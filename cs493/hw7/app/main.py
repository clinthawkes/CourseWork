from flask import Flask, request, redirect, render_template, flash 
from google.cloud import datastore
from requests_oauthlib import OAuth2Session
from google.oauth2 import id_token
from google.auth import crypt
from google.auth import jwt
from google.auth.transport import requests as authRequest
from helper import getState
import requests
import json
import constants

# This disables the requirement to use HTTPS so that you can test locally.
import os 
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

app = Flask(__name__)
client = datastore.Client()

# This is the page that you will use to decode and collect the info from
# the Google authentication flow
oauth = OAuth2Session(constants.clientId, redirect_uri=constants.redirectURL,
                          scope=constants.scope)

@app.route('/')
def index():
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
        return render_template('user.html', first=s.json()['names'][0]['givenName'], last=s.json()['names'][0]['familyName'], jwt=jwt)

@app.route('/oauth')
def oauth2():
    entity_key = client.key('state', constants.entityId)
    entity = client.get(key=entity_key)

    if 'code' not in request.args:
        state = getState() 
        entity.update({"state": state})
        client.put(entity)
        authURL = ('https://accounts.google.com/o/oauth2/v2/auth?response_type=code'
                    '&client_id={}&redirect_uri={}&scope={}&state={}').format(constants.clientId,
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


@app.route('/boats', methods=['POST','GET'])
def boats_get_post():
    token = request.headers.get("Authorization")
    content = request.get_json()

    if request.method == 'POST':
        if not token:
            error = {"Error": "Must provide a JWT"}
            return (json.dumps(error), 401)

        token = token.split(' ')
        token = token[1]
        req = authRequest.Request()
        try:
            id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
        except:
            error = {"Error": "JWT is not valid"}
            return (json.dumps(error), 401)
        
        if "sub" not in id_info:
            error = {"Error": "JWT is not valid"}
            return (json.dumps(error), 401)

        if "name" in content and "type" in content and  "length" in content and "public" in content:
            new_boat = datastore.entity.Entity(key=client.key(constants.boats))
            new_boat.update({"name": content["name"], "type": content["type"],
              "length": content["length"], "public": content["public"], "owner": id_info["sub"]})
            client.put(new_boat)
            new_boat["id"] = new_boat.key.id
            new_boat["self"] = constants.boats_url + str(new_boat.key.id)
            return (json.dumps(new_boat), 201)
        else:
            error = {"Error":"The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        if not token:
            query = client.query(kind=constants.boats)
            query.add_filter("public", "=", True)
            results = list(query.fetch())

            for e in results:
                e["id"] = e.key.id
                e["self"] = constants.boats_url + str(e.key.id)
            return (json.dumps(results), 200)

        else:
            token = token.split(' ')
            token = token[1]
            req = authRequest.Request()
            try:
                id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
            except:
                query = client.query(kind=constants.boats)
                query.add_filter("public", "=", True)
                results = list(query.fetch())
                for e in results:
                    e["id"] = e.key.id
                    e["self"] = constants.boats_url + str(e.key.id)
                return (json.dumps(results), 200)

            query = client.query(kind=constants.boats)
            query.add_filter("owner", "=", id_info['sub'])
            results = list(query.fetch())

            for e in results:
                e["id"] = e.key.id
                e["self"] = constants.boats_url + str(e.key.id)
            return (json.dumps(results), 200)


@app.route('/boats/<id>', methods=['DELETE'])
def boats_delete(id):
    boat_key = client.key(constants.boats, int(id))
    boat = client.get(key=boat_key)
    token = request.headers.get("Authorization")

    if not token:
        error = {"Error": "Must provide JWT"}
        return (json.dumps(error), 401)

    if not boat:
        error = {"Error": "No boat with this boat_id exists"}
        return (json.dumps(error), 403)

    token = token.split(' ')
    token = token[1]
    req = authRequest.Request()
    try:
        id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
    except:
        error = {"Error": "JWT must be valid"}
        return (json.dumps(error), 401)
    
    if "sub" not in id_info:
        error = {"Error": "JWT must be valid"}
        return (json.dumps(error), 401)

    if id_info['sub'] != boat['owner']: 
        error = {"Error": "Only the boat owner may delete boat"}
        return (json.dumps(error), 403)

    client.delete(boat_key)
    return ('',204)


@app.route('/owners/<id>/boats', methods=['GET'])
def owners_get(id):
    query = client.query(kind=constants.boats)
    query.add_filter("owner", "=", id)
    query.add_filter("public", "=", True)
    results = list(query.fetch())
    for e in results:
        e["id"] = e.key.id
        e["self"] = constants.boats_url + str(e.key.id)
    return (json.dumps(results), 200)


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)


# @app.route('/owners/<id>/boats', methods=['GET'])
# def owners_get(id):
#     query = client.query(kind=constants.boats)
            
#     if not token:
#         query.add_filter("owner", "=", id)
#         query.add_filter("public", "=", True)
#         results = list(query.fetch())
#         for e in results:
#             e["id"] = e.key.id
#             e["self"] = constants.boats_url + str(e.key.id)
#         return (json.dumps(results), 200)

#     token = token.split(' ')
#     token = token[1]
#     req = authRequest.Request()
#     try:
#         id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
#     except:
#         query.add_filter("owner", "=", id)
#         query.add_filter("public", "=", True)
#         results = list(query.fetch())
#         for e in results:
#             e["id"] = e.key.id
#             e["self"] = constants.boats_url + str(e.key.id)
#         return (json.dumps(results), 200)

#     if id == id_info["sub"]:
#         query.add_filter("owner", "=", id)
#         results = list(query.fetch())
#         for e in results:
#             e["id"] = e.key.id
#             e["self"] = constants.boats_url + str(e.key.id)
#         return (json.dumps(results), 200)
#     else:
#         query.add_filter("owner", "=", id)
#         query.add_filter("public", "=", True)
#         results = list(query.fetch())
#         for e in results:
#             e["id"] = e.key.id
#             e["self"] = constants.boats_url + str(e.key.id)
#         return (json.dumps(results), 200)

# # This link will redirect users to begin the OAuth flow with Google
# @app.route('/')
# def index():
#     authorization_url, state = oauth.authorization_url(
#         'https://accounts.google.com/o/oauth2/auth',
#         # access_type and prompt are Google specific extra
#         # parameters.
#         access_type="offline", prompt="select_account")
#     return render_template('welcome.html', authURL=authorization_url)

# # This is where users will be redirected back to and where you can collect
# # the JWT for use in future requests
# @app.route('/oauth')
# def oauthroute():
#     try:
#         token = oauth.fetch_token(
#             'https://accounts.google.com/o/oauth2/token',
#             authorization_response=request.url,
#             client_secret=constants.clientSecret)
#     except:
#         redirect('/')
#     else:
#         req = requests.Request()
#         headers = {'Authorization': 'Bearer {}'.format(token["access_token"])}
#         s = requests.get('https://people.googleapis.com/v1/people/me?personFields=names', headers=headers)
#         return render_template('user.html', first=s.json()['names'][0]['givenName'], last=s.json()['names'][0]['familyName'], jwt=token['id_token'])
