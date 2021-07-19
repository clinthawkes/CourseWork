from google.cloud import datastore
from flask import Flask, request
import json
import constants

app = Flask(__name__)
client = datastore.Client()

@app.route('/')
def index():
    return "Please navigate to /boats or /slips to use this API"\

@app.route('/boats', methods=['POST','GET'])
def boats_get_post():
    if request.method == 'POST':
        content = request.get_json()

        if "name" in content and "type" in content and  "length" in content:
            new_boat = datastore.entity.Entity(key=client.key(constants.boats))
            new_boat.update({"name": content["name"], "type": content["type"],
              "length": content["length"]})
            client.put(new_boat)
            new_boat["id"] = new_boat.key.id
            new_boat["self"] = constants.boats_url + str(new_boat.key.id)
            return (json.dumps(new_boat), 201)
        else:
            error = {"Error":"The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        query = client.query(kind=constants.boats)
        results = list(query.fetch())

        for e in results:
            e["id"] = e.key.id
            e["self"] = constants.boats_url + str(e.key.id)
        return (json.dumps(results), 200)

@app.route('/boats/<id>', methods=['GET', 'PATCH', 'DELETE'])
def boats_get_patch_delete(id):
    boat_key = client.key(constants.boats, int(id))
    boat = client.get(key=boat_key)

    if not boat:
        error = {"Error": "No boat with this boat_id exists"}
        return (json.dumps(error), 404)

    if request.method == 'GET':
        boat["id"] = boat.key.id
        boat["self"] = constants.boats_url + str(boat.key.id)
        return (json.dumps(boat),200)

    elif request.method == 'PATCH':
        content = request.get_json()

        if "name" in content and "type" in content and  "length" in content:
            boat.update({"name": content["name"], "type": content["type"],
              "length": content["length"]})
            client.put(boat)
            boat["id"] = boat.key.id
            boat["self"] = constants.boats_url + str(boat.key.id)
            return (json.dumps(boat),200)
        else:
            error = {"Error": "The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'DELETE':
        query = client.query(kind=constants.slips)
        results = list(query.fetch())

        for s in results:
            if s["current_boat"] == boat.key.id:
                slip_key = client.key(constants.slips, s.key.id)
                slip = client.get(key=slip_key)
                s.update({"current_boat": None})
                client.put(s)

        client.delete(boat_key)
        return ('',204)

@app.route('/slips', methods=['POST','GET'])
def slips_get_post():
    if request.method == 'POST':
        content = request.get_json()

        if "number" in content:
            new_slip = datastore.entity.Entity(key=client.key(constants.slips))
            new_slip.update({"number": content["number"], "current_boat": None})
            client.put(new_slip)
            new_slip["id"] = new_slip.key.id
            new_slip["self"] = constants.slips_url + str(new_slip.key.id)
            return (json.dumps(new_slip), 201)
        else:
            error = {"Error":"The request object is missing the required number"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        query = client.query(kind=constants.slips)
        results = list(query.fetch())

        for e in results:
            e["id"] = e.key.id
            e["self"] = constants.slips_url + str(e.key.id)
        return (json.dumps(results), 200)

@app.route('/slips/<id>', methods=['GET', 'DELETE'])
def slips_get_patch_delete(id):
    slip_key = client.key(constants.slips, int(id))
    slip = client.get(key=slip_key)

    if not slip:
        error = {"Error": "No slip with this slip_id exists"}
        return (json.dumps(error), 404)

    if request.method == 'GET':
        slip["id"] = slip.key.id
        slip["self"] = constants.slips_url + str(slip.key.id)
        return (json.dumps(slip),200)

    elif request.method == 'DELETE':
        client.delete(slip_key)
        return ('',204)

@app.route('/slips/<sid>/<bid>', methods=['PUT', 'DELETE'])
def slips_boat_put_delete(sid, bid):
    slip_key = client.key(constants.slips, int(sid))
    slip = client.get(key=slip_key)

    boat_key = client.key(constants.boats, int(bid))
    boat = client.get(key=boat_key)

    if request.method == 'PUT':
        if not slip or not boat:
            error = {"Error": "The specified boat and/or slip does not exist"}
            return (json.dumps(error), 404)

        if slip["current_boat"]:
            error = {"Error": "The slip is not empty"}
            return (json.dumps(error), 403)

        slip.update({"current_boat": boat.key.id})
        client.put(slip)
        return ('',204)

    elif request.method == 'DELETE':
        if not boat or not slip or slip["current_boat"] != boat.key.id:
            error = {"Error": "No boat with this boat_id is at the slip with this slip_id"}
            return (json.dumps(error), 404)

        else:
            slip.update({"current_boat": None})
            client.put(slip)
            return ('',204)


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
