# Proyecto_1
# Manual Usuario Proyecto 1 MIA

### Omar Alejandro Vides Esteban - 201709146

Es una aplicación que simula el funcionamiento de un administrador de archivos capaz de crear discos y formatearlos con sistemas de archivos que simulan un sistema EXT2 o EXT3.

La aplicación se ejecuta desde el ejecutable ***main*** recibiendo los comandos a manera de argumentos al momento de ejecutables. En el caso de desear crear carpetas y discos en carpetas fuera de la carpeta de usuario, es necesario ejecutar la aplicación con sudo.

> ./main /\*comando*/
	> o
> sudo ./main /\*comando*/

Para la ejecución de múltiples comandos a la vez se soporta el comando exec, el cual leerá un archivos con los comandos a ejecutar y mostrara los comentarios. 

## Comandos soportados

#### mkdisk
Este comando creará un archivo binario que simulará un disco duro, estos archivos binarios tendrán la extensión disk y su contenido al inicio será 0. Deberá ocupar físicamente el tamaño indicado por los parámetros, (no importa que el sistema operativo no muestre el tamaño exacto). Recibirá el nombre del archivo que simulará el disco duro y tendrá los siguientes parámetros:
Parametros:
| nombre  | categoria 	|	descripcion  |   
|--|--| -- |
| -size | obligatorio | indica el tamanio |
| -fit | opcional | indica el tipo de fit a usar |
| -unit | opcional | indica la unidad a usar del param size, puede ser K o M.  Por default es M|
| -path | obligatorio | ruta destino del archivo |


#### rmdisk
Este parámetro elimina un archivo que representa a un disco duro mostrando un mensaje de confirmación para eliminar. Tendrá los siguientes parámetros:
Parametros:
| nombre  | categoria 	|	descripcion  |   
|--|--| -- |
| -path | obligatorio | ruta del archivo a eliminar |


 
#### fdisk
Este comando administra las particiones en el archivo que representa al disco duro. Deberá mostrar un error si no se pudo realizar la operación solicitada sobre la partición, especificando por qué razón no pudo crearse (Por espacio, por restricciones de particiones, etc.).
No se considerará el caso de que se pongan parámetros incompatibles, por
ejemplo, en un mismo comando fdisk llamar a delete y add. La estructura de cada disco se explicará más adelante. Tendrá los siguientes parámetros:
Parametros:
| nombre  | categoria 	|	descripcion  |   
|--|--| -- |
| -size | obligatorio | indica el tamanio |
| -unit | opcional | indica la unidad a usar del param size, puede ser B, K o M.  Por default es K|
| -path | obligatorio | ruta del archivo |
| -type | opcional | tipo de particion puede ser P, E o L |
| -fit | opcional | indica el tipo de fit a usar |
| -delete | opcional | indica la particion a eliminar |
| -name | obligatorio | ruta destino del archivo |
| -add | obligatorio | sirve para modificar o agregar espacio del documento |

#### mount
Este comando montará una partición del disco en el sistema. Cada partición se
identificará por un id que tendrá la siguiente estructura: VD + LETRA + NUMERO. Por ejemplo: vda1, vda2, vdb1, vdc1… La letra será la misma para particiones en el mismo disco y el número diferente para particiones en el mismo disco. Los parámetros admitidos por este comando son:
Parametros:

| nombre  | categoria 	|	descripcion  |   
 |--|--|--|
 | -path | obligatorio | Este parámetro será la ruta en la que se encuentra el disco que se montará en el sistema. Este archivo ya debe existir. |
 | -name | -obligatorio | Indica el nombre de la partición a cargar. Si no existe debe mostrar error. |

#### unmount
Desmonta una partición del sistema. Se utilizará el id que se le asignó a la partición al momento de cargarla. Recibirá los siguientes parámetros:
Parametros:

| nombre  | categoria 	|	descripcion  |   
 |--|--|--|
 | -id | obligatorio | Especifica el id de la partición que se desmontará. Si no existe el id deberá mostrar un error |
#### mkfs
Este comando realiza un formateo completo de la partición, se formateará como
ext2 por defecto si en caso el comando fs no está definido. También creará un
archivo en la raíz llamado users.txt que tendrá los usuarios y contraseñas del sistema de archivos. La estructura de este archivo se explicará más adelante.
Parametros:

 | nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -id | obligatorio | Especifica el id de la partición que se desmontará. Si no existe el id deberá mostrar un error |
 | -type | opcional | Indicará que tipo de formateo se realizará. Ya que es opcional, se tomará como un formateo completo si no se especifica esta opción. Podrá tener los siguientes valores: Fast y Full |
 | -fs | opcional | Indica el sistema de archivos a formatear ext2 / ext3. Por defecto será ext2. Y los valores serán. 2fs para ext2 o 2fs para ext3 |
### Administracion de Usuarios y Grupos
#### login
Este comando se utiliza para iniciar sesión en el sistema. No se puede iniciar otra sesión sin haber hecho un logout antes, si no, debe mostrar un mensaje de error indicando que debe cerrar sesión antes. Recibirá los siguientes parámetros:
Parametros:

 | nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -usr | obligatorio| Especifica el nombre del usuario que iniciará sesión. Si no se encuentra mostrará un mensaje indicando que el usuario no existe. En este caso si distinguirá mayúsculas de minúsculas. |
 | -pwd | obligatorio | Indicará la contraseña del usuario, si no coincide debe mostrar un mensaje de autenticación fallida. Distinguirá entre mayúsculas y minúsculas. |
 | -id | obligatorio | Especifica el id de la partición que se desmontará. Si no existe el id deberá mostrar un error |
#### logout
Esta comando cierra sesión del usuario actualmente logeado.
#### mkgrp
Este comando creará un grupo para los usuarios de la partición y se guardará en el archivo users.txt de la partición, este comando solo lo puede utilizar el usuario root. Si otro usuario lo intenta ejecutar, deberá mostrar un mensaje de error, si el grupo a ingresar ya existe deberá mostrar un mensaje de error. Recibirá los siguientes parámetros:
Parámetros:
| nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -name | obligatorio| Indicará el nombre que tendrá el grupo |
 
#### rmgrp
Este comando eliminará un grupo para los usuarios de la partición. Solo lo puede utilizar el usuario root, si lo utiliza alguien más debe mostrar un error. Recibirá los siguientes parámetros:
Parámetros:
| nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -name | obligatorio| Indicará el nombre del grupo a eliminar. Si el grupo no se encuentra dentro de la partición debe mostrar un error. |
#### mkusr
Este comando crea un usuario en la partición. Solo lo puede ejecutar el usuario root, si lo utiliza otro usuario deberá mostrar un error. Recibirá los siguientes parámetros:
Parámetros:
| nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -usr | obligatorio| Indicará el nombre del usuario a crear, si ya existe, deberá mostrar un error indicando que ya existe el usuario. Máximo: 10 caracteres. |
 | -pwd | obligatorio| Indicará la contraseña del usuario. Máximo: 10 caracteres. |
 | -grp | obligatorio| Indicará el grupo al que pertenecerá el usuario. Debe de existir en la partición en la que se está creando el usuario, si no debe mostrar un mensaje de error. Máximo: 10 caracteres.|
#### rmusr
Este comando elimina un usuario en la partición. Solo lo puede ejecutar el usuario root, si lo utiliza otro usuario deberá mostrar un error. Recibirá los siguientes parámetros:
Parámetros:
| nombre | categoria 	|	descripcion  |   
 |--|--|--|
 | -usr | obligatorio| Indicará el nombre del usuario a eliminar, si no existe, deberá mostrar un error indicando que el usuario no existe.|

#### Titulo
| Parametro| Categoria |Descripcion  |
|--|--|--|
|  |  |  |

#### chmod
| Parametro| Categoria |Descripcion  |
|--|--|--|
| -path | Obligatorio |Este parámetro será la ruta en la que se encuentra el archivo o carpeta a la que se le cambiarán los permisos  |
| -ugo | Obligatorio | Indica los permisos que tendrán los usuarios. Serán tres números, uno para el Usuario, el siguiente para el Grupo al que pertenece el usuario y el último para Otros usuarios fuera del grupo. Cada número tendrá los valores desde el 0 al 7. |
|-R  | Opcional | Indica que el cambio será recursivo en el caso de carpetas. El cambio afectará a todos los archivos y carpetas en la que la ruta contenga la carpeta especificada por el parámetro –path y que sean propiedad del usuario actual |
 
 ####  mkfile 
| Parametro| Categoria |Descripcion  |
|--|--|--|
| -path | Obligatorio |  Este parámetro será la ruta del archivo que se creará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si ya existe debe sobre escribir el archivo.|
| -p | Opcional | Si se utiliza este parámetro y las carpetas especificadas por el parámetro –path no existen, entonces deben crearse las carpetas padres. Si ya existen, no deberá crear las carpetas. No recibirá ningún valor, si lo recibe debe mostrar error. |
| -size | Opcional | Este parámetro indicará el tamaño en bytes del archivo, el contenido serán números del 0 al 9 cuantas veces sea necesario. Si no se utiliza este parámetro, el tamaño será 0 bytes. Si es negativo debe mostrar error.|
| -cont| Opcional | Indicará un archivo en el disco duro de la computadora que tendráel contenido del archivo. Se utilizará para cargar contenido en el archivo. La ruta ingresada debe existir, si no mostrará un mensaje de error |

#### cat
 Parametro| Categoria |Descripcion  |
|--|--|--|
| -filen | Obligatorio | Permitirá Admitir como argumentos una lista de n ficheros que hay que enlazar. Estos se encadenarán en el mismo orden en el cual fueron especificados. Si no existe el archivo no tiene permiso de lectura, debe mostrarse un mensaje de error |

#### rm
| Parametro| Categoria |Descripcion  |
|--|--|--|
| -path | Obligatorio |Este parámetro será la ruta del archivo o carpeta que se eliminará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe el archivo o no tiene permisos de escritura en la carpeta o en el archivo, debe mostrarse un mensaje de error  |

#### edit
| Parametro| Categoria |Descripcion  |
|--|--|--|
| -path | Obligatorio | Este parámetro será la ruta del archivo que se modificará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe, debe mostrar un mensaje de error  |
| -size | Opcional* | Este parámetro indicará el nuevo tamaño en bytes del archivo, el contenido serán números del 0 al 9 cuantas veces sea necesario. Si es negativo debe mostrar error. |
| -cont | Opcional* | Indicará un archivo en el disco duro de la computadora que tendrá el nuevo contenido del archivo. Se utilizará para cargar contenido en el archivo. La ruta ingresada debe existir, si no mostrará un mensaje de error. |

#### ren
| Parametro| Categoria |Descripcion  |
|--|--|--|
| -path | Obligatorio | Este parámetro será la ruta del archivo o carpeta al que se le cambiará el nombre. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe el archivo o carpeta o no tiene permisos de escritura sobre la carpeta o archivo, debe mostrarse un mensaje de error. |
| -name | Obligatorio | Especificará el nuevo nombre del archivo, debe verificar que no exista un archivo con el mismo nombre, de ser así debe mostrar un mensaje de error. |

#### mkdir
Comando utilizado para la creacion de carpetas. El propietario sera el usuario con sesion activa, si el usuario no tiene permiso de escritura en la carpeta padre, se mostrara un error.

|Parametro|Categoria|Descripcion|
|--|--|--|
|-path| Obligatorio| Este parámetro será la ruta de la carpeta que se creará. Si no existen las carpetas padres, debe mostrar error, a menos que se utilice  el parámetro  –p,  que se  explica posteriormente
|-p | Opcional | Si  se utiliza  este  parámetro  y las  carpetas  padres  en  el  parámetro path  no existen,  entonces  deben  crearse.  Si ya existen, no realizará nada. No recibirá ningún valor,si lo recibedebe  mostrar error


#### cp
Este  comando  permitirá  realizar  una  copia  del  archivo  o  carpeta  y  todo  su contenido  hacia  otro destino.

|Parametro|Categoria|Descripcion|
|--|--|--|
|-path|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se  desea  copiar.  Si  lleva  espacios  en  blanco  deberá  encerrarse  entre  comillas.  Debe copiar todos los  archivos y carpetas con todo su  contenido, alos cuales tenga permiso de lectura. Si no tiene  permiso de lectura,  no realiza la  copia únicamente de  ese  archivo  o  carpeta.  Muestra  un  error  si no  existe  la ruta.|
|-dest| Obligatorio| Este parámetro será la  ruta de la carpeta a la que se  copiará elarchivo o carpeta. Debe tener permiso de  escritura sobre la  carpeta. Si lleva espacios en blanco  deberá encerrarse entre  comillas.  Debe mostrar un mensaje de error si no tiene permisos  paraescribir  o  si la  carpeta  no  existe|

#### mv
Este comando moverá un archivo o carpeta y todo su  contenido hacia otro destino.  Si el origen y  destino están dentro de la misma partición, solo cambiará las  referencias, para que ya no tenga el  padre  origen  sino,  el  padre  destino,  y  que  los  
padres  de  la  carpeta  o  archivo  ya  no  tengan  como  hijoa la  carpeta o archivo que se  movió. Solo se deberán verificar los permisos de escritura sobre la  carpeta  o  archivo  origen.

|Parametro|Categoria|Descripcion|
|--|--|--|
|-path|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se  desea  copiar.  Si  lleva  espacios  en  blanco  deberá  encerrarse  entre  comillas.  Debe copiar todos los archivos y carpetas con todo su  contenido, alos cuales tenga permiso de lectura. Si no tiene  permiso de lectura,  no realiza la  copia únicamente de  ese  archivo  o  carpeta.  Muestra  un  error  si no  existe  la ruta.|
|-dest|Obligatorio|Este parámetro será la ruta de la carpeta a la que se  copiará el  archivo o carpeta. Debe tener permiso de  escritura sobre la carpeta. Si  lleva  espacios en  blanco  deberá encerrarse  entre  comillas.  Debe mostrar un mensaje de error si no tiene permisos  para escribiro si la  carpeta no  existe.

#### find
Este comando  permitirá realizar una búsqueda por el nombre del archivo o carpeta.  Permitirá los  siguientes  caracteres  especiales:
|Caracter|Descripcion|
|--|--|
|?|Un solo caracter|
|*|Uno  o  más  caracteres|

Recibira los siguientes parametros:
|Parametro|Categoria|Descripcion|
|--|--|--|
|-path|Obligatorio| Este parámetro será la ruta de la carpeta en el que se  inicia la  búsqueda, deberá buscar en todo su contenido.  Si lleva espacios enblanco deberá  encerrarse  entre  comillas.  Debe  tener  permisos  de  lectura  en  los  archivos  que  buscará.
|-name|Obligatorio|Indica  el  nombre  del  archivo  o carpeta  que  se  está  buscando.  Debe  aceptar  los  caracteres  especiales definidos anteriormente|

El resultado debe mostrarse en forma de árbol, mostrando todos los archivos  encontrados. find *  mostrará toda la estructura del sistema de archivos a partir de  la carpeta indicada ya que no hay  filtro.  De  no  mostrarse  en  forma de árbol  esto  no  
será  válido

#### chown
Cambiará  el  propietario  de  uno  o  varios  archivos  o  carpetas.  Lo  podrá  utilizar  el  usuario  root  en  todos  los archivos o carpetas y también lo podrán utilizar otros  usuarios, pero  solo  sobre sus  propios  archivos.  Recibirá  los  siguientes parámetros:
|Parametro|Categoria|Descripcion|
|--|--|--|
|-path|Obligatorio| Este parámetro será la ruta en la que se encuentra el  archivo o  carpeta  a  la  que se le  cambiará  el  propietario.  Si  no existe  la  ruta  deberá  mostrar  mensaje  de error.|
|-R|Opcional|Este parámetro será la ruta en la que se encuentra el  archivo o  carpeta  a  la  que se le  cambiará  el  propietario.  Si  no existe  la  ruta  deberá  mostrar  mensaje  de error.|
|-usr|Obligatorio|Nombre  del  nuevo propietario del  archivo  o  carpeta.  Si  no  existe  o  esta  eliminado debe  mostrar  error.

#### chgrp
Cambiará  el  grupo  al  que  pertenece  el  usuario.  Únicamente  lo  podrá  utilizar  el  usuario  root.  Recibirálos  siguientes  parámetros:
|Parametro|Categoria|Descripcion|
|--|--|--|
|-usr|Obligatorio|Especifica  el  nombre  del  usuario  al  que  se  le  cambiará  de  grupo.  Si  no  existe  debe  mostrar  un  error.|
|-grp|Obligatorio|Contendrá  el  nombre del  nuevo  grupo al  que pertenecerá  el  usuario.  Si  no  existe  o  está  eliminado  debe  mostrar  un  error.
