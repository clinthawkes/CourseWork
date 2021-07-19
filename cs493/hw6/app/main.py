from flask import Flask, redirect, request, render_template, flash 
from google.cloud import datastore
import requests
import json
import constants
from helper import getState

app = Flask(__name__)
client = datastore.Client()


@app.route('/')
def index():
    entity_key = client.key('state', constants.entityId)
    entity = client.get(key=entity_key)
    state = entity.get('state')
    if state == None:
        return render_template('welcome.html')
    else:
        headers = {'Authorization': 'Bearer {}'.format(entity["token"])}
        s = requests.get('https://people.googleapis.com/v1/people/me?personFields=names', headers=headers)
        entity.update({"state": None, "token": None})
        client.put(entity)
        return render_template('user.html', first=s.json()['names'][0]['givenName'], last=s.json()['names'][0]['familyName'], state=state)

@app.route('/oauth')
def oauth():
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
            entity.update({"token": token})
            client.put(entity)
            return redirect('/') 


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
