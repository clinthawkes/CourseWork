from flask import Blueprint, request, make_response
from google.cloud import datastore
import json
import constants

relationship_bp = Blueprint('relationship_bp', __name__)
client = datastore.Client()

@relationship_bp.endpoint('relationship')
def passengers_flight_put_delete(fid, pid):
    passenger_key = client.key(constants.passengers, int(pid))
    passenger = client.get(key=passenger_key)

    flight_key = client.key(constants.flights, int(fid))
    flight = client.get(key=flight_key)

    if request.method == 'PUT':
        if not passenger or not flight:
            error = {"Error": "The specified flight and/or passenger does not exist"}
            res = make_response(json.dumps(error))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 404
            return res

        if int(fid) in passenger["flights"]:
            error = {"Error": "The passenger is already on a flight"}
            res = make_response(json.dumps(error))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 403
            return res

        if len(flight["passengers"]) < flight["capacity"]:
            passenger["flights"].append(int(fid))
            client.put(passenger)
            flight["passengers"].append(int(pid))
            client.put(flight)
            return ('',204)
        else:
            error = {"Error": "Flight is at capacity"}
            res = make_response(json.dumps(error))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 403
            return res


    elif request.method == 'DELETE':
        if not flight or not passenger or int(fid) not in passenger["flights"]:
            error = {"Error": "No flight with this flight_id has a passenger with this passenger_id"}
            res = make_response(json.dumps(error))
            res.headers.set('Content-Type', 'application/json')
            res.status_code = 404
            return res

        else:
            flight["passengers"].remove(int(pid))
            client.put(flight)
            passenger["flights"].remove(int(fid))
            client.put(passenger)
            return ('',204)

    else:
            error = {"Error": "Method not allowed"}
            res = make_response(json.dumps(error))
            res.headers.set('Content-Type', 'application/json')
            res.headers.set('Allow', 'PUT, DELETE')
            res.status_code = 405
            return res