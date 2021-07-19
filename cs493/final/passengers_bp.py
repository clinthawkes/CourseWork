from flask import Blueprint, request, make_response
from google.cloud import datastore
from validation import valLocation, valName, valBirthday
import json
import constants

passengers_bp = Blueprint('passengers_bp', __name__)
client = datastore.Client()

@passengers_bp.endpoint('passengers')
def passengers_get_post():
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

        if "name" in content and "birthday" in content and "country" in content:
            if valName(content["name"]) and valBirthday(content["birthday"]) and valLocation(content["country"]):
                new_passenger = datastore.entity.Entity(key=client.key(constants.passengers))
                new_passenger.update({"name": content["name"], "birthday": content["birthday"], 
                    "country": content["country"], "flights": []})
                client.put(new_passenger)
                new_passenger["id"] = new_passenger.key.id
                new_passenger["self"] = constants.passengers_url + str(new_passenger.key.id)
                res = make_response(json.dumps(new_passenger))
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
            error = {"Error":"The request object is missing at least one of the required attributes"}
            res = make_response(json.dumps(error))
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

        query = client.query(kind=constants.passengers)
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
            e["self"] = constants.passengers_url + str(e.key.id)
            if e["flights"]:
                data = []
                for i in e["flights"]:
                    data.append({"id": int(i), "self": constants.flights_url + str(i)})
                e["flights"] = data
        output = {"passengers": results}
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


@passengers_bp.endpoint('passengers<id>')
def passengers_get_patch_put_delete(id):
    passenger_key = client.key(constants.passengers, int(id))
    passenger = client.get(key=passenger_key)
    
    if not passenger:
        error = {"Error": "No passenger with this passenger_id exists"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 404
        return res

    if request.method == 'GET':
        if 'application/json' not in request.accept_mimetypes:
            error1 = {"Error": "The response must be json or html"}
            res = make_response(json.dumps(error1))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        passenger["id"] = passenger.key.id
        passenger["self"] = constants.passengers_url + str(passenger.key.id)
        if passenger["flights"]:
            data = []
            for i in passenger["flights"]:
                data.append({"id": int(i), "self": constants.flights_url + str(i)})
            passenger["flights"] = data
        res = make_response(json.dumps(passenger))
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

        if "name" in content:
            if valName(content["name"]):
                passenger.update({"name": content["name"]})
            else:
                error3 = {"Error": "The 'name' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error3))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "birthday" in content:
            if valBirthday(content["birthday"]):
                passenger.update({"birthday": content["birthday"]})
            else:
                error5 = {"Error": "The 'birthday' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error5))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "country" in content:
            if valLocation(content["country"]):
                passenger.update({"country": content["country"]})
            else:
                error6 = {"Error": "The 'country' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error6))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        client.put(passenger)
        passenger["id"] = passenger.key.id
        passenger["self"] = constants.passengers_url + str(passenger.key.id)
        if passenger["flights"]:
            data = []
            for i in passenger["flights"]:
                data.append({"id": int(i), "self": constants.flights_url + str(i)})
            passenger["flights"] = data
        res = make_response(json.dumps(passenger))
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

        if "name" in content and "birthday" in content and  "country" in content:
            if valName(content["name"]) and valBirthday(content["birthday"]) and valLocation(content["country"]):
                passenger.update({"name": content["name"], "birthday": content["birthday"],
                    "country": content["country"]})
                client.put(passenger)
                passenger["id"] = passenger.key.id
                passenger["self"] = constants.passengers_url + str(passenger.key.id)
                if passenger["flights"]:
                    data = []
                    for i in passenger["flights"]:
                        data.append({"id": int(i), "self": constants.flights_url + str(i)})
                    passenger["flights"] = data
                res = make_response(json.dumps(passenger))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 200
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
        if passenger["flights"]:
            for l in passenger["flights"]:
                flight_key = client.key(constants.flights, int(l))
                flight = client.get(key=flight_key)
                flight["passengers"].remove(passenger.key.id)
                client.put(flight)

        client.delete(passenger_key)
        return ('',204)

    else:
        error = {"Error": "Method not allowed"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.headers.set('Allow', 'GET, PUT, PATCH, DELETE')
        res.status_code = 405
        return res