import requests
import pytest
import requests_mock

from main import app
from unittest.mock import patch


@pytest.fixture
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client


@pytest.fixture
def mock_peliculas_no_vacio():
    return [
        {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
        {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'}
    ]


@pytest.fixture
def mock_peliculas_vacio():
    return []


def test_obtener_peliculas(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.get('http://localhost:5000/peliculas')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 2


def test_obtener_peliculas_vacio(client, mock_peliculas_vacio):
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.get('http://localhost:5000/peliculas')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 0


def test_obtener_pelicula(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.get('http://localhost:5000/peliculas/1')
        assert response.status_code == 200
        assert response.get_json()['id'] == 1
        assert response.get_json()['titulo'] == 'Indiana Jones'


def test_obtener_pelicula_vacio(client, mock_peliculas_vacio):
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.get('http://localhost:5000/peliculas/1')
        assert response.get_json()['error'] == 'Pelicula no encontrada'
        assert response.status_code == 404


def test_agregar_pelicula(client, mock_peliculas_no_vacio):
    nueva_pelicula = {'titulo': 'Pelicula de prueba', 'genero': 'Acción'}
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.post(
            'http://localhost:5000/peliculas', json=nueva_pelicula)
        assert response.status_code == 201
        assert response.get_json()['id'] == 3


def test_obtener_detalle_pelicula(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.get('http://localhost:5000/peliculas/1')
        assert response.status_code == 200
        assert response.get_json()['titulo'] == 'Indiana Jones'


def test_obtener_detalle_pelicula_vacio(client, mock_peliculas_vacio):
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.get('http://localhost:5000/peliculas/1')
        assert response.get_json()['error'] == 'Pelicula no encontrada'
        assert response.status_code == 404


def test_actualizar_detalle_pelicula(client, mock_peliculas_no_vacio):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.put(
            'http://localhost:5000/peliculas/1', json=datos_actualizados)
        assert response.status_code == 200
        assert response.get_json()['titulo'] == 'Nuevo título'


def test_actualizar_detalle_pelicula_vacio(client, mock_peliculas_vacio):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.put(
            'http://localhost:5000/peliculas/1', json=datos_actualizados)
        assert response.get_json()['error'] == 'Pelicula no encontrada'
        assert response.status_code == 404


def test_eliminar_pelicula(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.delete('http://localhost:5000/peliculas/1')
        assert response.status_code == 200


def test_eliminar_pelicula_vacio(client, mock_peliculas_vacio):
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.delete('http://localhost:5000/peliculas/1')
        assert response.get_json()['error'] == 'Pelicula no encontrada'
        assert response.status_code == 404


def test_listar_peliculas_nombre(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        nombre = 'indiana'
        response = client.get(
            f'http://localhost:5000/peliculas/nombre/{nombre}')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 1
        assert data[0]['titulo'] == 'Indiana Jones'


def test_listar_peliculas_nombre_vacio(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        nombre = 'no existe'
        response = client.get(
            f'http://localhost:5000/peliculas/nombre/{nombre}')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 0


def test_listar_peliculas_genero(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'acción'
        response = client.get(
            f'http://localhost:5000/peliculas/genero/{genero}')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 2
        assert data[0]['genero'] == 'Acción'
        assert data[1]['genero'] == 'Acción'


def test_listar_peliculas_genero_vacio(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'comedia'
        response = client.get(
            f'http://localhost:5000/peliculas/genero/{genero}')
        assert response.status_code == 200
        data = response.get_json()
        assert len(data) == 0


def test_obtener_pelicula_aleatoria(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        response = client.get('http://localhost:5000/peliculas/random')
        assert response.status_code == 200
        data = response.get_json()
        assert data['id'] in [1, 2]


def test_obtener_pelicula_aleatoria_vacio(client, mock_peliculas_vacio):
    with patch('main.peliculas', mock_peliculas_vacio):
        response = client.get('http://localhost:5000/peliculas/random')
        assert response.status_code == 404


def test_obtener_pelicula_aleatorio_genero(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'acción'
        response = client.get(
            f'http://localhost:5000/peliculas/random/genero/{genero}')
        assert response.status_code == 200
        data = response.get_json()
        assert data['genero'] == 'Acción'


def test_obtener_pelicula_aleatorio_genero_vacio(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'comedia'
        response = client.get(
            f'http://localhost:5000/peliculas/random/genero/{genero}')
        assert response.status_code == 404


def test_obtener_pelicula_feriado(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'acción'
        response = client.get(
            f'http://localhost:5000/peliculas/feriado/genero/{genero}')
        assert response.status_code == 200
        data = response.get_json()
        assert data['pelicula_recomendada']['genero'] == 'Acción'


def test_obtener_pelicula_feriado_vacio(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'comedia'
        response = client.get(
            f'http://localhost:5000/peliculas/feriado/genero/{genero}')
        assert response.status_code == 404


def test_obtener_pelicula_feriado_genero_existente(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'acción'
        response = client.get(
            f'http://localhost:5000/peliculas/feriado/genero/{genero}')
        assert response.status_code == 200
        data = response.get_json()
        assert data['pelicula_recomendada']['genero'] == 'Acción'
        assert data['feriado'] is not None


def test_obtener_pelicula_feriado_genero_no_existente(client, mock_peliculas_no_vacio):
    with patch('main.peliculas', mock_peliculas_no_vacio):
        genero = 'comedia'
        response = client.get(
            f'http://localhost:5000/peliculas/feriado/genero/{genero}')
        assert response.status_code == 404
        data = response.get_json()
        assert data['error'] == 'No hay películas disponibles para el género especificado'
