from flask import Flask, request, make_response
from werkzeug.routing import Rule
from validation import *
from json2html import *
import json
import constants

app = Flask(__name__)
app.url_map.add(Rule('/', endpoint='index'))
app.url_map.add(Rule('/boats', endpoint = 'boats_post'))
app.url_map.add(Rule('/boats/', endpoint = 'boats_null'))
app.url_map.add(Rule('/boats/<id>', endpoint = 'boats_get_put_patch_delete'))


@app.endpoint('index')
def index():
    return "Please navigate to /boats to use this API"\

@app.endpoint('boats_post')
def boats_post():
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

        if "name" in content and "type" in content and  "length" in content:
            if valName(content["name"]) and valType(content["type"]) and valLength(content["length"]):
                if uniqueName(content["name"]):
                    new_boat = datastore.entity.Entity(key=client.key(constants.boats))
                    new_boat.update({"name": content["name"], "type": content["type"],
                        "length": content["length"]})
                    client.put(new_boat)
                    new_boat["id"] = new_boat.key.id
                    new_boat["self"] = constants.boats_url + str(new_boat.key.id)
                    res = make_response(json.dumps(new_boat))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 201
                    return res
                else:
                    error5 = {"Error": "That name is already in use"}
                    res = make_response(json.dumps(error5))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 400
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

    # if request.method == 'GET':
    #     query = client.query(kind=constants.boats)
    #     results = list(query.fetch())
    #     for b in results:
    #         b["id"] = b.key.id
    #         b["self"] = constants.boats_url + str(b.key.id)
    #     res = make_response(json.dumps(results))
    #     res.headers.set('Allow', 'POST')
    #     res.headers.set('Content-Type', 'application/json')
    #     res.status_code = 200
    #     return res

    else:
        res = make_response(json.dumps({"Error": "Method not allowed"}))
        res.headers.set('Allow', 'POST')
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 405
        return res

@app.endpoint('boats_null')
def boats_null():
    error = {"Error": "Boat ID must not be null"}
    res = make_response(json.dumps(error))
    res.headers.set('Content-Type', 'application/json')
    res.status_code = 400
    return res

@app.endpoint('boats_get_put_patch_delete')
def boats_get_put_patch_delete(id):
    boat_key = client.key(constants.boats, int(id))
    boat = client.get(key=boat_key)
    if not boat:
        error = {"Error": "No boat with this boat_id exists"}
        res = make_response(json.dumps(error))
        res.headers.set('Content-Type', 'application/json')
        res.status_code = 404
        return res

    if request.method == 'GET':
        if 'application/json' and 'text/html' not in request.accept_mimetypes:
            error1 = {"Error": "The response must be json or html"}
            res = make_response(json.dumps(error1))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 406
            return res

        boat["id"] = boat.key.id
        boat["self"] = constants.boats_url + str(boat.key.id)
        if 'application/json' in request.accept_mimetypes:
            res = make_response(json.dumps(boat))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 200
            return res
        else:
            res = make_response(json2html.convert(json = json.dumps(boat)))
            res.headers.set('Content-Type', 'text/html')
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
        if "id" in content:
            error2 = {"Error": "You are not allowed to change the boat ID"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 403
            return res


        if "name" in content:
            if valName(content["name"]):
                if uniqueName(content["name"]):
                    boat.update({"name": content["name"]})
                else:
                    error4 = {"Error": "That name is already in use"}
                    res = make_response(json.dumps(error4))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 400
                    return res
            else:
                error3 = {"Error": "The 'name' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error3))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "type" in content:
            if valType(content["type"]):
                boat.update({"type": content["type"]})
            else:
                error5 = {"Error": "The 'type' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error5))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        if "length" in content:
            if valLength(content["length"]):
                boat.update({"length": content["length"]})
            else:
                error6 = {"Error": "The 'length' attribute in the request does not conform to the required type/format"}
                res = make_response(json.dumps(error6))
                res.headers.set('Content-Type', 'application/json')
                res.status_code = 400
                return res

        client.put(boat)
        boat["id"] = boat.key.id
        boat["self"] = constants.boats_url + str(boat.key.id)
        res = make_response(json.dumps(boat))
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

        content = request.get_json()
        if "id" in content:
            error2 = {"Error": "You are not allowed to change the boat ID"}
            res = make_response(json.dumps(error2))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 403
            return res


        if "name" in content and "type" in content and  "length" in content:
            if valName(content["name"]) and valType(content["type"]) and valLength(content["length"]):
                if uniqueName(content["name"]):
                    boat.update({"name": content["name"], "type": content["type"],
                        "length": content["length"]})
                    client.put(boat)
                    res = make_response('')
                    res.headers.set('Location', constants.boats_url + str(boat.key.id))
                    res.status_code = 303
                    return res
                else:
                    error5 = {"Error": "That name is already in use"}
                    res = make_response(json.dumps(error5))
                    res.headers.set('Content-Type', 'application/json')
                    res.status_code = 400
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
        client.delete(boat_key)
        return ('',204)

    else:
        res = make_response(json.dumps({"Error": "Method not allowed"}))
        res.headers.set('Allow', 'GET, PUT, PATCH, DELETE')
        res.status_code = 405
        return res


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
