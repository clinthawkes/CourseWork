from flask import Blueprint, make_response, request
from google.cloud import datastore
import json
import constants
 
user_bp = Blueprint('user_bp', __name__)
client = datastore.Client()

@user_bp.endpoint('users')
def users():
    if request.method == 'GET': 
        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        query = client.query(kind=constants.users)
        results = list(query.fetch())
        data = []
        for account in results:
            data.append({"id": account["id"]})
        res = make_response(json.dumps(data))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 200 
        return res

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET')
        res.status_code = 405
        return res