SELECT AVG(songs.energy) FROM songs JOIN artists ON artists.name = 'Drake' AND artists.id = songs.artist_id;