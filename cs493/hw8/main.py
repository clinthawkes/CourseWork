from google.cloud import datastore
from flask import Flask, request
import json
import constants

app = Flask(__name__)
client = datastore.Client()

@app.route('/')
def index():
    return "Please navigate to /boats use this API"\

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
            return (json.dumps(new_boat), 201)
        else:
            error = {"Error":"The request object is missing at least one of the required attributes"}
            return (json.dumps(error), 400)

    elif request.method == 'GET':
        query = client.query(kind=constants.boats)
        results = list(query.fetch())
        for e in results:
            e["id"] = e.key.id
        output = {"Boats": results}
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
        return (json.dumps(boat),200)

    elif request.method == 'DELETE':
        client.delete(boat_key)
        return ('',204)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
