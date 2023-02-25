from requests import Response


def response(status_code, jsonb):
    response = Response()
    response.status_code = status_code
    response._content = jsonb
    response._query = ''
    return response
