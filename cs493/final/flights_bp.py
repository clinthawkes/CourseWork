from flask import Blueprint, request, make_response
from google.cloud import datastore
from google.oauth2 import id_token
from google.auth.transport import requests as authRequest
from validation import valDate, valCapacity, valLocation
import json
import constants

flights_bp = Blueprint('flights_bp', __name__)
client = datastore.Client()

@flights_bp.endpoint('flights')
def flights_get_post():
    token = request.headers.get("Authorization")
    if not token:
        error = {"Error": "Must provide a JWT"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 401 
        return res

    token = token.split(' ')
    token = token[1]
    req = authRequest.Request()
    try:
        id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
    except:
        error = {"Error": "JWT is not valid"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 401 
        return res

    if request.method == 'POST':
        if 'application/json' not in request.content_type:
            error1 = {"Error": "The request object must be json"}
            res = make_response(json.dumps(error1))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 415
            return res

        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        content = request.get_json()

        if "date" in content and "capacity" in content and  "origin" in content and  "destination" in content:
            if valDate(content["date"]) and valCapacity(content["capacity"]) and valLocation(content["origin"]) and valLocation(content["destination"]):
                new_flight = datastore.entity.Entity(key=client.key(constants.flights))
                new_flight.update({"date": content["date"], "capacity": content["capacity"],
                    "origin": content["origin"], "destination": content["destination"], "owner": id_info["sub"], "passengers": []})
                client.put(new_flight)
                new_flight["id"] = new_flight.key.id
                new_flight["self"] = constants.flights_url + str(new_flight.key.id)
                res = make_response(json.dumps(new_flight))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 201
                return res
            else:
                error4 = {"Error": "One or more of the request attributes do not conform to the required type/format"}
                res = make_response(json.dumps(error4))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res
        else:
            error3 = {"Error":"The request object is missing at least one of the required attributes"}
            res = make_response(json.dumps(error3))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 400
            return res

    elif request.method == 'GET':
        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        query = client.query(kind=constants.flights)
        query.add_filter("owner", "=", id_info["sub"])
        q_limit = int(request.args.get('limit', '5'))
        q_offset = int(request.args.get('offset', '0'))
        l_iterator = query.fetch(limit= q_limit, offset=q_offset)
        pages = l_iterator.pages
        results = list(next(pages))
        if l_iterator.next_page_token:
            next_offset = q_offset + q_limit
            next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)
        else:
            next_url = None
        for e in results:
            e["id"] = e.key.id
            e["self"] = constants.flights_url + str(e.key.id)
            data = []
            for l in e["passengers"]:
                data.append({"id": l, "self": constants.passengers_url + str(l)})
            e["passengers"] = data
        output = {"flights": results}
        if next_url:
            output["next"] = next_url
        collection = list(query.fetch())
        output["total_count"] = len(collection)
        res = make_response(json.dumps(output))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 200
        return res

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET, POST')
        res.status_code = 405
        return res


@flights_bp.endpoint('flights<id>')
def flights_get_put_patch_delete(id):
    flight_key = client.key(constants.flights, int(id))
    flight = client.get(key=flight_key)

    if not flight:
        error = {"Error": "No flight with this flight_id exists"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 404
        return res

    token = request.headers.get("Authorization")

    if not token:
        error = {"Error": "Must provide a JWT"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 401
        return res

    token = token.split(' ')
    token = token[1]
    req = authRequest.Request()

    try:
        id_info = id_token.verify_oauth2_token(token, req, constants.clientId)
    except:
        error = {"Error": "JWT is not valid"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 401
        return res

    if id_info["sub"] != flight["owner"]:
        error = {"Error": "Only the flight owner can perform this operation"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 403
        return res

    if request.method == 'GET':
        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        flight["id"] = flight.key.id
        flight["self"] = constants.flights_url + str(id)
        data = []
        for l in flight["passengers"]:
            data.append({"id": l, "self": constants.passengers_url + str(l)})
        flight["passengers"] = data
        res = make_response(json.dumps(flight))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 200 
        return res

    elif request.method == 'PATCH':
        if 'application/json' not in request.content_type:
            error1 = {"Error": "The request object must be json"}
            res = make_response(json.dumps(error1))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 415
            return res

        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        content = request.get_json()

        if "date" in content:
            if valDate(content["date"]):
                flight.update({"date": content["date"]})
            else:
                error3 = {"Error": "The 'date' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error3))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "capacity" in content:
            if valCapacity(content["capacity"]):
                if int(content["capacity"]) >= len(flight["passengers"]):
                    flight.update({"capacity": content["capacity"]})
                else:
                    error5 = {"Error": "New capacity value is less than the number of assigned passengers. Please delete the flight and create a new one."}
                    res = make_response(json.dumps(error5))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 403
                    return res

            else:
                error5 = {"Error": "The 'capacity' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error5))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "origin" in content:
            if valLocation(content["origin"]):
                flight.update({"origin": content["origin"]})
            else:
                error6 = {"Error": "The 'origin' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error6))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "destination" in content:
            if valLocation(content["destination"]):
                flight.update({"destination": content["destination"]})
            else:
                error6 = {"Error": "The 'destination' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error6))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res
                
        client.put(flight)
        flight["id"] = flight.key.id
        flight["self"] = constants.flights_url + str(flight.key.id)
        res = make_response(json.dumps(flight))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 200
        return res

    elif request.method == 'PUT':
        if 'application/json' not in request.content_type:
            error1 = {"Error": "The request object must be json"}
            res = make_response(json.dumps(error1))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 415
            return res

        if 'application/json' not in request.accept_mimetypes:
            error2 = {"Error": "The response must be json"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        content = request.get_json()
        
        if "date" in content and "capacity" in content and  "origin" in content and "destination" in content:
            if valDate(content["date"]) and valCapacity(content["capacity"]) and valLocation(content["origin"]) and valLocation(content["destination"]):
                if int(content["capacity"]) >= len(flight["passengers"]):
                    flight.update({"date": content["date"], "capacity": content["capacity"],
                        "origin": content["origin"], "destination": content["destination"]})
                    client.put(flight)
                    flight["id"] = flight.key.id
                    flight["self"] = constants.flights_url + str(flight.key.id)
                    res = make_response(json.dumps(flight))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 200 
                    return res
                else:
                    error5 = {"Error": "New capacity value is less than the number of assigned passengers. Please delete the flight and create a new one."}
                    res = make_response(json.dumps(error5))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 403
                    return res
            else:
                error4 = {"Error": "One or more of the request attributes do not conform to the required type/format"}
                res = make_response(json.dumps(error4))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res
        else:
            error3 = {"Error":"The request object is missing at least one of the required attributes"}
            res = make_response(json.dumps(error3))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 400
            return res
            
    elif request.method == 'DELETE':
        if flight["passengers"]:
            for l in flight["passengers"]:
                passenger_key = client.key(constants.passengers, int(l))
                passenger = client.get(key=passenger_key)
                passenger["flights"].remove(flight.key.id)
                client.put(passenger)

        client.delete(flight_key)
        return ('',204)

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET, PUT, PATCH, DELETE')
        res.status_code = 405
        return res