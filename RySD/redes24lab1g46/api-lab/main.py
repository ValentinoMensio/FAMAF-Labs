from flask import Flask, jsonify, request
import random
from proximo_feriado import NextHoliday

app = Flask(__name__)
peliculas = [
    {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
    {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
    {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
    {'id': 4, 'titulo': 'Jurassic Park', 'genero': 'Aventura'},
    {'id': 5, 'titulo': 'The Avengers', 'genero': 'Acción'},
    {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
    {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
    {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
    {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'},
    {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'},
    {'id': 11, 'titulo': 'Pulp Fiction', 'genero': 'Crimen'},
    {'id': 12, 'titulo': 'Fight Club', 'genero': 'Drama'}
]


@app.route('/peliculas', methods=['GET'])
def obtener_peliculas():
    return jsonify(peliculas), 200


@app.route('/peliculas/<int:id>', methods=['GET'])
def obtener_pelicula(id):
    # Lógica para buscar la película por su ID y devolver sus detalles

    pelicula = next(
        (pelicula for pelicula in peliculas if pelicula['id'] == id), None)
    if pelicula:
        return jsonify(pelicula), 200
    else:
        return jsonify({'error': 'Pelicula no encontrada'}), 404


@app.route('/peliculas', methods=['POST'])
def agregar_pelicula():
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    print(peliculas)
    return jsonify(nueva_pelicula), 201


@app.route('/peliculas/<int:id>', methods=['PUT'])
def actualizar_pelicula(id):
    # Lógica para buscar la película por su ID y actualizar sus detalles

    pelicula = next(
        (pelicula for pelicula in peliculas if pelicula['id'] == id), None)
    if pelicula:
        pelicula_actualizada = {
            'id': id,
            'titulo': request.json['titulo'],
            'genero': request.json['genero']
        }
        return jsonify(pelicula_actualizada), 200
    else:
        return jsonify({'error': 'Pelicula no encontrada'}), 404


@app.route('/peliculas/<int:id>', methods=['DELETE'])
def eliminar_pelicula(id):
    # Lógica para buscar la película por su ID y eliminarla

    pelicula = next(
        (pelicula for pelicula in peliculas if pelicula['id'] == id), None)
    if pelicula:
        peliculas.remove(pelicula)
        return jsonify({'mensaje': 'Película eliminada correctamente'}), 200
    else:
        return jsonify({'error': 'Pelicula no encontrada'}), 404


@app.route('/peliculas/nombre/<nombre>', methods=['GET'])
def listar_peliculas_nombre(nombre):
    # implemente la funcionalidad de búsqueda de películas, devolviendo la lista de películas que tengan determinado string en el título.

    peliculas_encontradas = [
        pelicula for pelicula in peliculas if nombre.lower() in pelicula['titulo'].lower()]

    return jsonify(peliculas_encontradas), 200


@app.route('/peliculas/genero/<genero>', methods=['GET'])
def listar_peliculas_genero(genero):
    # Implementa la funcionalidad para devolver el listado de películas de un género específico.

    peliculas_por_genero = [
        pelicula for pelicula in peliculas if pelicula['genero'].lower() == genero.lower()]
    return jsonify(peliculas_por_genero)


@app.route('/peliculas/random', methods=['GET'])
def obtener_pelicula_aleatoria():
    if not peliculas:
        return jsonify({'error': 'No hay películas disponibles'}), 404

    return jsonify(random.choice(peliculas)), 200


@app.route('/peliculas/random/genero/<genero>', methods=['GET'])
# Implementa la funcionalidad para devolver una película aleatoria de un género específico.
def obtener_pelicula_aleatorio_genero(genero):
    peliculas_por_genero = [
        pelicula for pelicula in peliculas if pelicula['genero'].lower() == genero.lower()]

    if not peliculas_por_genero:
        return jsonify({'error': 'No hay películas disponibles para el género especificado'}), 404

    return jsonify(random.choice(peliculas_por_genero)), 200


@app.route('/peliculas/feriado/genero/<genero>', methods=['GET'])
def obtener_pelicula_feriado(genero):
    # Obtener la próxima fecha de feriado y recomendar una película que se ajuste al género solicitado para ese día.

    proximo_feriado = NextHoliday()
    proximo_feriado.fetch_holidays()

    pelicula_recomendada = [
        pelicula for pelicula in peliculas if pelicula['genero'].lower() == genero.lower()]

    if not pelicula_recomendada:
        return jsonify({'error': 'No hay películas disponibles para el género especificado'}), 404

    pelicula_recomendada = random.choice(pelicula_recomendada)
    return jsonify({'feriado': proximo_feriado.holiday, 'pelicula_recomendada': pelicula_recomendada}), 200


def obtener_nuevo_id():
    if len(peliculas) > 0:
        ultimo_id = peliculas[-1]['id']
        return ultimo_id + 1
    else:
        return 1


app.add_url_rule('/peliculas', 'obtener_peliculas',
                 obtener_peliculas, methods=['GET'])
app.add_url_rule('/peliculas/<int:id>', 'obtener_pelicula',
                 obtener_pelicula, methods=['GET'])
app.add_url_rule('/peliculas', 'agregar_pelicula',
                 agregar_pelicula, methods=['POST'])
app.add_url_rule('/peliculas/<int:id>', 'actualizar_pelicula',
                 actualizar_pelicula, methods=['PUT'])
app.add_url_rule('/peliculas/<int:id>', 'eliminar_pelicula',
                 eliminar_pelicula, methods=['DELETE'])
app.add_url_rule('/peliculas/genero/<genero>', 'listar_peliculas_genero',
                 listar_peliculas_genero, methods=['GET'])
app.add_url_rule('/peliculas/nombre/<nombre>', 'listar_peliculas_nombre',
                 listar_peliculas_nombre, methods=['GET'])
app.add_url_rule('/peliculas/random', 'obtener_pelicula_aleatoria',
                 obtener_pelicula_aleatoria, methods=['GET'])
app.add_url_rule('/peliculas/random/genero/<genero>', 'obtener_pelicula_aleatorio_genero',
                 obtener_pelicula_aleatorio_genero, methods=['GET'])


if __name__ == '__main__':
    app.run()
