# UTAD-UI-FPS-Public
 
El codigo esta todo documentado, lo único que considero importante de comentar es que para la vinculación de la barra de recarga, puesto que se realiza en el weapon component y al inicio no existe el weapon component, se crea un delegado desde el player que notifica cuando recoge el arma y en ese momento se bindea a un delegado para el envio de la notificación del tiempo.
