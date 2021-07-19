from google.cloud import datastore
from flask import Flask, request
import json
import constants

app = Flask(__name__)
client = datastore.Client()

@app.route('/')
def index():
    return "Please navigate to /boats or /loads to use this API"\

@app.route('/boats', methods=['POST','GET'])
def boats_get_post():
    if request.method == 'POST':
        content = request.get_json()

        if "name" in content and "type" in content and  "length" in content:
            new_boat = datastore.entity.Entity(key=client.key(constants.boats))
            new_boat.update({"name": content["name"], "type": content["type"],
              "length": content["length"], "loads": []})
            client.put(new_boat)
            new_boat["id"] = new_boat.key.id
            new_boat["self"] = constants.boats_url + str(new_boat.key.id)
            return (json.dumps(new_boat), 201)
        else:
            error = {"Error":"The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        query = client.query(kind=constants.boats)
        q_limit = int(request.args.get('limit', '3'))
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
            e["self"] = constants.boats_url + str(e.key.id)
            data = []
            for l in e["loads"]:
                data.append({"id": l, "self": constants.loads_url + str(l)})
            e["loads"] = data
        output = {"Boats": results}
        if next_url:
            output["next"] = next_url
        return (json.dumps(output), 200)

@app.route('/boats/<id>', methods=['GET', 'DELETE'])
def boats_get_delete(id):
    boat_key = client.key(constants.boats, int(id))
    boat = client.get(key=boat_key)

    if not boat:
        error = {"Error": "No boat with this boat_id exists"}
        return (json.dumps(error), 404)

    if request.method == 'GET':
        boat["id"] = boat.key.id
        boat["self"] = constants.boats_url + str(id)
        data = []
        for l in boat["loads"]:
            data.append({"id": l, "self": constants.loads_url + str(l)})
        boat["loads"] = data
        return (json.dumps(boat),200)

    elif request.method == 'DELETE':
        if boat["loads"]:
            for l in boat["loads"]:
                load_key = client.key(constants.loads, int(l))
                load = client.get(key=load_key)
                load["carrier"] = None
                client.put(load)

        client.delete(boat_key)
        return ('',204)

@app.route('/boats/<id>/loads', methods=['GET'])
def boats_get_loads(id):
    boat_key = client.key(constants.boats, int(id))
    boat = client.get(key=boat_key)

    if not boat:
        error = {"Error": "No boat with this boat_id exists"}
        return (json.dumps(error), 404)

    data = []
    for l in boat["loads"]:
        load_key = client.key(constants.loads, l)
        load = client.get(key=load_key)
        load["id"] = load.key.id
        load["self"] = constants.loads_url + str(load.key.id)
        bid = load["carrier"]
        load["carrier"] = {"id": bid, "self": constants.boats_url + str(bid)}
        data.append(load)
    result = {"Loads": data}
    return (json.dumps(result),200)

@app.route('/loads', methods=['POST','GET'])
def loads_get_post():
    if request.method == 'POST':
        content = request.get_json()

        if "weight" in content and "content" in content and "delivery_date" in content:
            new_load = datastore.entity.Entity(key=client.key(constants.loads))
            new_load.update({"weight": content["weight"], "content": content["content"], 
                "delivery_date": content["delivery_date"], "carrier": None})
            client.put(new_load)
            new_load["id"] = new_load.key.id
            new_load["self"] = constants.loads_url + str(new_load.key.id)
            return (json.dumps(new_load), 201) 
        else:
            error = {"Error":"The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        query = client.query(kind=constants.loads)
        q_limit = int(request.args.get('limit', '3'))
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
            e["self"] = constants.loads_url + str(e.key.id)
            if e["carrier"]:
                bid = e["carrier"]
                e["carrier"] = {"id": bid, "self": constants.boats_url + str(bid)}
        output = {"Loads": results}
        if next_url:
            output["next"] = next_url
        return (json.dumps(output), 200)

@app.route('/loads/<id>', methods=['GET', 'DELETE'])
def loads_get_delete(id):
    load_key = client.key(constants.loads, int(id))
    load = client.get(key=load_key)

    if not load:
        error = {"Error": "No load with this load_id exists"}
        return (json.dumps(error), 404)

    if request.method == 'GET':
        load["id"] = load.key.id
        load["self"] = constants.loads_url + str(load.key.id)
        if load["carrier"]:
            temp = load["carrier"]
            load.update({"carrier": {"id": temp, "self": constants.boats_url + str(temp)}})
        return (json.dumps(load),200)

    elif request.method == 'DELETE':
        if load["carrier"]:
            boat_key = client.key(constants.boats, load["carrier"])
            boat = client.get(key=boat_key)
            boat["loads"].remove(int(id))
            client.put(boat)

        client.delete(load_key)
        return ('',204)

@app.route('/boats/<bid>/loads/<lid>', methods=['PUT', 'DELETE'])
def loads_boat_put_delete(bid, lid):
    load_key = client.key(constants.loads, int(lid))
    load = client.get(key=load_key)

    boat_key = client.key(constants.boats, int(bid))
    boat = client.get(key=boat_key)

    if request.method == 'PUT':
        if not load or not boat:
            error = {"Error": "The specified boat and/or load does not exist"}
            return (json.dumps(error), 404)

        if load["carrier"]:
            error = {"Error": "The load is already on a boat"}
            return (json.dumps(error), 403)

        load["carrier"] = int(bid)
        client.put(load)
        if boat["loads"]:
            boat["loads"].append(int(lid))
        else:
            boat["loads"] = [int(lid)] 
        client.put(boat)
        return ('',204)

    elif request.method == 'DELETE':
        if not boat or not load or load["carrier"] != boat.key.id:
            error = {"Error": "No boat with this boat_id has a load with this load_id"}
            return (json.dumps(error), 404)

        else:
            boat["loads"].remove(int(lid))
            client.put(boat)
            load["carrier"] = None
            client.put(load)
            return ('',204)


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
