from flask import Blueprint, request, redirect, make_response, render_template, flash
from google.cloud import datastore
from google.oauth2 import id_token
from google.auth.transport import requests as authRequest
from helper import getState
import requests
import json
import constants

oauth_bp = Blueprint('oauth_bp', __name__)
client = datastore.Client()

@oauth_bp.endpoint('index')
def index():
    if request.method == 'GET':
        entity_key = client.key('state', constants.entityId)
        entity = client.get(key=entity_key)
        jwt = entity['jwt']

        if jwt == None:
            return render_template('welcome.html')
        else:
            headers = {'Authorization': 'Bearer {}'.format(entity["token"])}
            s = requests.get('https://people.googleapis.com/v1/people/me?personFields=names', headers=headers)
            entity.update({"state": None, "token": None, "jwt": None})
            client.put(entity)

            req = authRequest.Request()
            try:
                id_info = id_token.verify_oauth2_token(jwt, req, constants.clientId)
            except:
                error = {"Error": "JWT is not valid"}
                res = make_response(json.dumps(error))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 401 
                return res
            
            query = client.query(kind=constants.users)
            query.add_filter("id", "=", id_info["sub"])
            results = list(query.fetch())
            
            if not results:
                new_user = datastore.entity.Entity(key=client.key(constants.users))
                new_user.update({"id": id_info["sub"]})
                client.put(new_user)
                flash('New account has been created!', 'success')
                return render_template('user.html', first=s.json()['names'][0]['givenName'], last=s.json()['names'][0]['familyName'], jwt=jwt, sub=id_info["sub"])
            else:
                query = client.query(kind=constants.flights)
                query.add_filter("owner", "=", id_info["sub"])
                results = list(query.fetch())
                data = []
                for r in results:
                    data.append(r.key.id)
                return render_template('user.html', first=s.json()['names'][0]['givenName'], last=s.json()['names'][0]['familyName'], jwt=jwt, sub=id_info["sub"], data=data)

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET')
        res.status_code = 405
        return res


@oauth_bp.endpoint('oauth')
def oauth2():
    if request.method == 'GET':
        entity_key = client.key('state', constants.entityId)
        entity = client.get(key=entity_key)

        if 'code' not in request.args:
            state = getState() 
            entity.update({"state": state})
            client.put(entity)
            authURL = ('https://accounts.google.com/o/oauth2/v2/auth?response_type=code'
                        '&client_id={}&redirect_uri={}&scope={}&state={}&prompt=consent').format(constants.clientId,
                        constants.redirectURL, constants.scope, state)
            return redirect(authURL) 
        else:
            if entity["state"] == request.args.get('state'):
                authCode = request.args.get('code')
                data = {'code': authCode,
                        'client_id': constants.clientId,
                        'client_secret': constants.clientSecret,
                        'redirect_uri': constants.redirectURL,
                        'grant_type': 'authorization_code'}
                r = requests.post('https://oauth2.googleapis.com/token', data=data) 
                token = r.json()['access_token'] 
                jwt = r.json()['id_token']
                entity.update({"token": token, "jwt": jwt})
                client.put(entity)
                return redirect('/') 

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET')
        res.status_code = 405
        return res