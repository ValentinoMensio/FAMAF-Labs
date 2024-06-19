import requests

# Obtener todas las películas
print("Obteniendo todas las películas...")
response = requests.get('http://localhost:5000/peliculas')
assert response.status_code == 200
assert len(response.json()) >= 12
peliculas = response.json()
print("Películas existentes:")
for pelicula in peliculas:
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Agregar una nueva película
print("Agregando una nueva película...")
nueva_pelicula = {
    'titulo': 'Fight Club',
    'genero': 'Acción'
}
response = requests.post(
    'http://localhost:5000/peliculas', json=nueva_pelicula)
if response.status_code == 201:
    pelicula_agregada = response.json()
    print("Película agregada:")
    print(
        f"ID: {pelicula_agregada['id']}, Título: {pelicula_agregada['titulo']}, Género: {pelicula_agregada['genero']}")
    assert pelicula_agregada['titulo'] == nueva_pelicula['titulo']
    assert pelicula_agregada['genero'] == nueva_pelicula['genero']
    assert pelicula_agregada['id'] >= 13
else:
    # condicion inesperada
    print("Error al agregar la película.")
    assert response.status_code == 500
print()


# Obtener detalles de una película específica
print("Obteniendo detalles de una película específica...")
id_pelicula = 2  # ID de la película a obtener
response = requests.get(f'http://localhost:5000/peliculas/{id_pelicula}')

assert response.status_code == 200
pelicula = response.json()
print("Detalles de la película:")
print(
    f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Obtener detalles de una película específica inexistente
print("Obteniendo detalles de una película específica inexistente...")
id_pelicula = 500  # ID de la película a obtener
response = requests.get(f'http://localhost:5000/peliculas/{id_pelicula}')
assert response.status_code == 404
print("Película no encontrada.")
print()


# Actualizar los detalles de una película
print("Actualizando los detalles de una película...")
id_pelicula = 2  # ID de la película a actualizar
datos_actualizados = {
    'titulo': 'Nuevo título',
    'genero': 'Comedia'
}
response = requests.put(
    f'http://localhost:5000/peliculas/{id_pelicula}', json=datos_actualizados)

assert response.status_code == 200, "Error: No se pudo actualizar la película."
# Verificación de los datos actualizados
pelicula_actualizada = response.json()
assert pelicula_actualizada['id'] == id_pelicula, "Error: ID de la película no coincide."
assert pelicula_actualizada['titulo'] == datos_actualizados[
    'titulo'], "Error: Título de la película no actualizado correctamente."
assert pelicula_actualizada['genero'] == datos_actualizados[
    'genero'], "Error: Género de la película no actualizado correctamente."

print("Película actualizada:")
print(
    f"ID: {pelicula_actualizada['id']}, Título: {pelicula_actualizada['titulo']}, Género: {pelicula_actualizada['genero']}")

print()


# Eliminar una película existente
print("Eliminando una película...")
id_pelicula = 1  # ID de la película a eliminar
response = requests.delete(f'http://localhost:5000/peliculas/{id_pelicula}')
assert response.status_code == 200, "Error: No se pudo eliminar la película."
print("Película eliminada correctamente.")
print()


# Eliminar una película inexistente
print("Eliminando una película inexistente...")
id_pelicula = 500  # ID de la película a eliminar
response = requests.delete(f'http://localhost:5000/peliculas/{id_pelicula}')
assert response.status_code == 404, "Error: Se eliminó una película inexistente."
print("Película no encontrada.")
print()


# Buscar películas por nombre
print("Buscando películas por nombre...")
nombre_pelicula = 'The'
response = requests.get(
    f'http://localhost:5000/peliculas/nombre/{nombre_pelicula}')
assert response.status_code == 200
peliculas_encontradas = response.json()
print("Películas encontradas:")
for pelicula in peliculas_encontradas:
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Buscar películas por nombre inexistente
print("Buscando películas por nombre...")
nombre_pelicula = 'Pulp Fiction: say what again'
response = requests.get(
    f'http://localhost:5000/peliculas/nombre/{nombre_pelicula}')
assert response.status_code == 200
peliculas_encontradas = response.json()
assert len(peliculas_encontradas) == 0
print("Película no encontrada.")
print()


# Listar películas de un género específico
print("Listando películas de un género específico...")
genero = 'Acción'
response = requests.get(f'http://localhost:5000/peliculas/genero/{genero}')
assert response.status_code == 200
peliculas_accion = response.json()
print(f"Películas de género '{genero}':")
for pelicula in peliculas_accion:
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Listar películas de un género específico no existente
print("Listando películas de un género específico...")
genero = 'Videojuegos'
response = requests.get(f'http://localhost:5000/peliculas/genero/{genero}')
assert response.status_code == 200
peliculas_accion = response.json()
print(f"Películas de género '{genero}':")
assert len(peliculas_accion) == 0
print("No hay películas de este género.")
print()


# Obtener pelicula random
print("Obteniendo una película aleatoria...")
response = requests.get(f'http://localhost:5000/peliculas/random')
assert response.status_code == 200, "Error al obtener una película aleatoria."
pelicula = response.json()

print("Detalles de la película:")
print(
    f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Obtener la próxima fecha de feriado y recomendar una película que se ajuste al género solicitado para ese día.
print("Obteniendo la próxima fecha de feriado y recomendando una película...")
genero = 'Drama'
response = requests.get(
    f'http://localhost:5000/peliculas/feriado/genero/{genero}')
assert response.status_code == 200, "Error al obtener la recomendación de película."
recomendacion = response.json()
assert 'feriado' in recomendacion
assert 'pelicula_recomendada' in recomendacion
print(
    f"El proximo feriado es el {recomendacion['feriado']['dia']}/{recomendacion['feriado']['mes']} con motivo de {recomendacion['feriado']['motivo']}. Te sugiero ver la pelicula de {recomendacion['pelicula_recomendada']['genero']} {recomendacion['pelicula_recomendada']['titulo']}")
print()


# Obtener la próxima fecha de feriado y recomendar una película que se ajuste al género solicitado inexistente para ese día.
print("Obteniendo la próxima fecha de feriado y recomendando una película...")
genero = 'Videojuegos'
response = requests.get(
    f'http://localhost:5000/peliculas/feriado/genero/{genero}')
assert response.status_code == 404
assert response.json() == {
    'error': 'No hay películas disponibles para el género especificado'}
print('No hay películas disponibles para el género especificado')
print()


# Obtener pelicula random por genero
print("Obteniendo una película aleatoria por género...")
genero = 'Drama'
response = requests.get(
    f'http://localhost:5000/peliculas/random/genero/{genero}')
assert response.status_code == 200, "Error al obtener una película aleatoria por género."
pelicula = response.json()

print("Detalles de la película:")
print(
    f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()


# Obtener pelicula random por genero inexistente
print("Obteniendo una película aleatoria por género inexistente...")
genero = 'Videojuegos'
response = requests.get(
    f'http://localhost:5000/peliculas/random/genero/{genero}')
assert response.status_code == 404
assert response.json() == {
    'error': 'No hay películas disponibles para el género especificado'}
print('No hay películas disponibles para el género especificado')
print()


print("Todos los tests pasaron exitosamente!")
