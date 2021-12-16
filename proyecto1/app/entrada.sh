#Contenido de calificacion.sh
#Crea 5 discos de 50 Mb

#CREANDO DISCOS ----------------------------------------------------------------------------------------
mkdisk -size~:~50 -unit~:~M -path~:~/home/archivos/faseU/Disco1.disk
mkdisk -unit~:~K -size~:~51200 -path~:~/home/archivos/faseU/Disco2.disk
mkDisk -size~:~10 -path~:~/home/archivos/faseU/Disco4.disk -unit~:~k
mkdisk -size~:~51200 -unit~:~k -path~:~"/home/archivos/faseU/misarchivos/Disco3.disk"
mkdisk -size~:~51200 -unit~:~k -path~:~"/home/archivos/faseU/misarchivos/mario/Escritorio/Disco5.disk"

#Debería dar error
mkDisk -param~:~x -size~:~30 -path~:~/home/archivos/faseU/Disco4.disk

#ELIMINANDO DISCOS ------------------------------------------------------------------------------------
#Elimina un D, el primero debería dar error
rmDisk -path~:~/home/Disco4.disk
rmDisk -path~:~/home/archivos/faseU/Disco2.disk
rmDisk -path~:~"/home/archivos/faseU/mis mario/Escritorio/Disco3.disk"

#CREANDO PARTICIONES ----------------------------------------------------------------------------------
#Crear particiones Disco1.disk
fdisk -type~:~P -unit~:~K -name~:~Part1 -size~:~7680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF
fdisk -type~:~E -unit~:~K -name~:~Part2 -size~:~7680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~WF
fdisk -type~:~E -unit~:~K -name~:~Part3 -size~:~7680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~WF #Debe dar error por que ya existe una extendida
fdisk -type~:~P -unit~:~K -name~:~Part3 -size~:~7680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~WF
fdisk -type~:~P -unit~:~K -name~:~Part4 -size~:~7680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part5 -size~:~1200 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part6 -size~:~1200 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part7 -size~:~1200 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~WF
fdisk -type~:~L -unit~:~K -name~:~Part8 -size~:~1200 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~WF
fdisk -type~:~L -unit~:~K -name~:~Part9 -size~:~1200 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part10 -size~:~1680 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~BF

#Crear particiones Disco2.disk
fdisk -type~:~L -unit~:~K -name~:~Part28 -size~:~7680 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF #Debe dar error porque no existe una extendida
fdisk -type~:~L -unit~:~K -name~:~Part27 -size~:~7680 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF #Debe dar error porque no existe una extendida
fdisk -type~:~P -unit~:~K -name~:~Part12 -size~:~4680 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~P -unit~:~K -name~:~Part13 -size~:~4680 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF
fdisk -type~:~P -unit~:~K -name~:~Part14 -size~:~4680 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~E -unit~:~K -name~:~Part15 -size~:~17360 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF
fdisk -type~:~L -unit~:~K -name~:~Part16 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part17 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part18 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF
fdisk -type~:~L -unit~:~K -name~:~Part19 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~WF
fdisk -type~:~L -unit~:~K -name~:~Part20 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part21 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part22 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part23 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF
fdisk -type~:~L -unit~:~K -name~:~Part24 -size~:~1200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~BF

#Monta las particiones Disco1.disk
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part1 #vda1
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part1 #Error ya esta montada
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part9 #Debe dar error por que no existe
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part8 #vda2
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part7 #vda3
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part6 #vda4
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part2 #vda5
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part3 #vda6
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part12 #vdb1
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part13 #vdb2
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part14 #vdb3
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part15 #vdb4
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part16 #vdb5
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part17 #vdb6
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part18 #vdb7
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part19 #vdb8
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part20 #vdb9
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part21 #vdb10
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part22 #vdb11
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part23 #vdb12
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part24 #vdb13
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part25 #vdb14 Debe dar error por qu no existe

#Desmontar las particiones
unmount -id~:~vda4
#Desmontar Error
unmount -id~:~vdx1

#Creando reportes
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep1/mbr1.png -name~:~mbr
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep1/disk1.png -name~:~disk
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep1/mbr4.png -name~:~mbr
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep1/disk4.png -name~:~disk

#Eliminando particiones
fdisk -delete~:~fast -name~:~Part1 -path~:~/home/archivos/faseU/Disco1.disk
fdisk -delete~:~fast -name~:~Part6 -path~:~/home/archivos/faseU/Disco1.disk
fdisk -delete~:~fast -name~:~Part2 -path~:~/home/archivos/faseU/Disco1.disk #No se puede porque tiene logicas
fdisk -delete~:~fast -name~:~Part10 -path~:~/home/archivos/faseU/Disco1.disk
fdisk -delete~:~fast -name~:~Part9 -path~:~/home/archivos/faseU/Disco1.disk

#Eliminando y agregando espacio tamaño de particiones
fdisk -delete~:~full -unit~:~K -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part14
fdisk -add~:~25 -unit~:~K -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part13

#Creando reportes
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep2/mbr2.png -name~:~mbr
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep2/disk2.png -name~:~disk
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep2/mbr5.png -name~:~mbr
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep2/disk5.png -name~:~disk

#Eliminando tamaño de particiones
fdisk -add~:~-700 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part3
fdisk -add~:~-800 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part4
fdisk -add~:~-200 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part11
fdisk -add~:~-400 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part8
fdisk -add~:~-1000 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part13
fdisk -add~:~-1000 -unit~:~K -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part13

#Creando reportes
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep3/mbr3.png -name~:~mbr
rep -id~:~vda1 -Path~:~/home/archivos/faseU/reportes/rep3/disk3.png -name~:~disk
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep3/mbr6.png -name~:~mbr
rep -id~:~vdb1 -Path~:~/home/archivos/faseU/reportes/rep3/disk6.png -name~:~disk

#Aseguramos eliminar los dos dicos para segunda fase
rmDisck -path~:~/home/archivos/faseU/Disco1.disk #Si
rmDisck -path~:~/home/archivos/faseU/Disco2.disk #Si

#Crea 2 discos
#CREANDO DISCOS ----------------------------------------------------------------------------------------
mkdisk -size~:~75 -unit~:~M -path~:~/home/archivos/faseU/Disco1.disk -fit~:~FF
mkdisk -unit~:~K -size~:~51200 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~FF

#CREANDO PARTICIONES ----------------------------------------------------------------------------------
#Crear particiones Disco1.disk
fdisk -type~:~P -unit~:~M -name~:~Part1 -size~:~20 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~FF
fdisk -type~:~P -unit~:~M -name~:~Part2 -size~:~15 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~FF
fdisk -type~:~P -unit~:~M -name~:~Part3 -size~:~20 -path~:~/home/archivos/faseU/Disco1.disk -fit~:~FF

#Crear particiones Disco2.disk
fdisk -type~:~P -unit~:~M -name~:~Part1_D2 -size~:~20 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~FF
fdisk -type~:~P -unit~:~M -name~:~Part2_D2 -size~:~10 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~FF
fdisk -type~:~P -unit~:~M -name~:~Part3_D2 -size~:~10 -path~:~/home/archivos/faseU/Disco2.disk -fit~:~FF

#Monta las particiones

mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part1 #vda1
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part2 #vda2
mount -path~:~/home/archivos/faseU/Disco1.disk -name~:~Part3 #vda3

mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part1_D2 #vdb1
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part2_D2 #vdb2
mount -path~:~/home/archivos/faseU/Disco2.disk -name~:~Part3_D2 #vdb3

#Crea el sistema de archivos en todas las particiones primarias
#fast reescribe el superbloque
#full poner /0 y luego reescribir el superbloque

mkfs -type~:~fast -id~:~vda1 -fs~:~3fs
mkfs -type~:~full -id~:~vda2 -fs~:~3fs
mkfs -type~:~fast -id~:~vda3 -fs~:~3fs

#Reporte1 ::::(  )
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte1_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte1_vda1_tree.jpg" -name~:~tree

pause

#Creando Usuarios
#Login como root en el vda1 - Part1 de tipo EXT2
#Debe dar error porque no existe el usuario roca
Login -pwd~:~567 -usr~:~roca -id~:~vda1
#debe dar error porque no existe nada activo
logout
#Debe dar error contraseña incorrecta
Login -pwd~:~12345 -usr~:~root -id~:~vda1
Login -pwd~:~123 -usr~:~root -id~:~vda1
#Debe dar error porque ya hay un login activo
lOgin -pwd~:~error -usr~:~error -id~:~vda1
pause

#Creando grupos en vda1
mkgrp -naMe~:~Archivos
mkgrp -NamE~:~SA
mkgrp -name~:~"Compi 2"
mkgrp -NamE~:~Grupo1
#Error en el mkgrp grupo ya existente
mkgrp -name~:~"Compi 2"

#Borrando Grupos
#Error no existe este grupo
rmgrp -name~:~"DB2"
rmgrp -name~:~SA

#Crearemos 3 usuarios llamados user1, user2, user3
Mkusr -usr~:~"user1" -grp~:~root -pwd~:~user1
Mkusr -usr~:~"user2" -grp~:~"Compi 2" -pwd~:~user2
Mkusr -usr~:~"user3" -grp~:~"Compi 2" -pwd~:~user3
#Da error porque ya existe ese usuario
Mkusr -usr~:~"user2" -grp~:~"Compi 2" -pwd~:~user2
#Da error porque no existe ese grupo
Mkusr -usr~:~"user2" -grp~:~SA -pwd~:~user2

rmusr -usr~:~user3
rmusr -usr~:~user3 #Debe dar error porque ya no existe
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/Manejo_Usuarios.svg" -ruta~:~"/users.txt" -name~:~file
pause

Mkdir -P  -path~:~/home/archivos/mia/faseU
Mkdir -P  -path~:~/home/archivos/mia/carpeta2
Mkdir -P  -path~:~/home/archivos/mia/z
Mkdir -P  -path~:~/home/archivos/mia/carpeta3/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
Mkdir -P  -path~:~/home/archivos/mia/carpeta4/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
Mkdir  -path~:~/home/archivos/mia/carpeta2/a1
Mkdir  -path~:~/home/archivos/mia/carpeta2/a2
Mkdir  -path~:~/home/archivos/mia/carpeta2/a3
Mkdir  -path~:~/home/archivos/mia/carpeta2/a4
Mkdir  -path~:~/home/archivos/mia/carpeta2/a5
Mkdir  -path~:~/home/archivos/mia/carpeta2/a6
Mkdir  -path~:~/home/archivos/mia/carpeta2/a7
Mkdir  -path~:~/home/archivos/mia/carpeta2/a8
Mkdir  -path~:~/home/archivos/mia/carpeta2/a9
Mkdir  -path~:~/home/archivos/mia/carpeta2/a10
#Error ya existente
Mkdir  -path~:~/home/archivos/mia/carpeta2/a10
Pause

logout
#PERMISOS EN ARCHIVOS Y CARPETAS
login -usr~:~user2 -pwd~:~user2 -id~:~vda1
mkfile -path~:~"/home/NOCREAR.txtS" -size~:~75
Pause

logout
loGin -usr~:~root -pwd~:~123 -id~:~vda1
#Archivo
mkfile -path~:~"/home/b1.txt" -size~:~75
#Debe dar error ruta no existe
mkfile -path~:~"/home/Noexiste/b1.txt" -size~:~75
#Debe dar error size negativo
mkfile -path~:~"/home/b1.txt" -size~:~-45
#archivo con parametro -p
mkfile -p -path~:~"/home/ahora/ya existe/b1.txt" -size~:~640
#File 1er Indirecto
mkfile -p -path~:~"/home/ind.txt" -size~:~1200
#reporte3 ::::(  )
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte3_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte3_vda1_tree.jpg" -name~:~tree

pause

#REMOVER
#Archivo Directos
rem -path~:~/home/ind.txt

#Reporte4 ::::(  )
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte4_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte4_vda1_tree.jpg" -name~:~tree

pause

#MOVER
#debe dar error porque no existe
mv -path~:~"/home/archivos/no existe" -dest~:~"/home"
mv -path~:~/home/archivos/mia/carpeta2/a10 -dest~:~"/home"

find -Path~:~"/" -name~:~"?.*"

Mkdir  -path~:~/home/archivos/mia/faseU/a1
Mkdir  -path~:~/home/archivos/mia/faseU/a2
Mkdir  -path~:~/home/archivos/mia/faseU/a3
Mkdir  -path~:~/home/archivos/mia/faseU/a4
Mkdir  -path~:~/home/archivos/mia/faseU/a5
Mkdir  -path~:~/home/archivos/mia/faseU/a6
Mkdir  -path~:~/home/archivos/mia/faseU/a7
Mkdir  -path~:~/home/archivos/mia/faseU/a8
Mkdir  -path~:~/home/archivos/mia/faseU/a9
Mkdir  -path~:~/home/archivos/mia/faseU/a10
Mkdir  -path~:~/home/archivos/mia/faseU/a11
Mkdir  -path~:~/home/archivos/mia/faseU/a12
Mkdir  -path~:~/home/archivos/mia/faseU/a13
Mkdir  -path~:~/home/archivos/mia/faseU/a14
Mkdir  -path~:~/home/archivos/mia/faseU/a15
Mkdir  -path~:~/home/archivos/mia/faseU/a16
Mkdir  -path~:~/home/archivos/mia/faseU/a17
Mkdir  -path~:~/home/archivos/mia/faseU/a18
Mkdir  -path~:~/home/archivos/mia/faseU/a19
Mkdir  -path~:~/home/archivos/mia/faseU/a20
Mkdir  -path~:~/home/archivos/mia/faseU/a21
Mkdir  -path~:~/home/archivos/mia/faseU/a22
Mkdir  -path~:~/home/archivos/mia/faseU/a23
Mkdir  -path~:~/home/archivos/mia/faseU/a24
Mkdir  -path~:~/home/archivos/mia/faseU/a25
Mkdir  -path~:~/home/archivos/mia/faseU/a26
Mkdir  -path~:~/home/archivos/mia/faseU/a27
Mkdir  -path~:~/home/archivos/mia/faseU/a28
Mkdir  -path~:~/home/archivos/mia/faseU/a29
Mkdir  -path~:~/home/archivos/mia/faseU/a30
Mkdir  -path~:~/home/archivos/mia/faseU/a31
Mkdir  -path~:~/home/archivos/mia/faseU/a32
Mkdir  -path~:~/home/archivos/mia/faseU/a33
Mkdir  -path~:~/home/archivos/mia/faseU/a34
Mkdir  -path~:~/home/archivos/mia/faseU/a35
Mkdir  -path~:~/home/archivos/mia/faseU/a36
Mkdir  -path~:~/home/archivos/mia/faseU/a37
Mkdir  -path~:~/home/archivos/mia/faseU/a38
Mkdir  -path~:~/home/archivos/mia/faseU/a39
Mkdir  -path~:~/home/archivos/mia/faseU/a40
Mkdir  -path~:~/home/archivos/mia/faseU/a41
Mkdir  -path~:~/home/archivos/mia/faseU/a42
Mkdir  -path~:~/home/archivos/mia/faseU/a43
Mkdir  -path~:~/home/archivos/mia/faseU/a44
Mkdir  -path~:~/home/archivos/mia/faseU/a45
Mkdir  -path~:~/home/archivos/mia/faseU/a46

#Primer indirecto
mkdir  -path~:~"/home/archivos/mia/faseU/b1"
mkdir  -path~:~"/home/archivos/mia/faseU/b2"
mkdir  -path~:~"/home/archivos/mia/faseU/b3"
mkdir  -path~:~"/home/archivos/mia/faseU/b4"
mkdir  -path~:~"/home/archivos/mia/faseU/b5"
mkdir  -path~:~"/home/archivos/mia/faseU/b6"
mkdir  -path~:~"/home/archivos/mia/faseU/b7"
mkdir  -path~:~"/home/archivos/mia/faseU/b8"
mkdir  -path~:~"/home/archivos/mia/faseU/b9"
mkdir  -path~:~"/home/archivos/mia/faseU/b10"
mkdir  -path~:~"/home/archivos/mia/faseU/b11"
mkdir  -path~:~"/home/archivos/mia/faseU/b12"
mkdir  -path~:~"/home/archivos/mia/faseU/b13"
mkdir  -path~:~"/home/archivos/mia/faseU/b14"
mkdir  -path~:~"/home/archivos/mia/faseU/b15"
mkdir  -path~:~"/home/archivos/mia/faseU/b16"
mkdir  -path~:~"/home/archivos/mia/faseU/b17"
mkdir  -path~:~"/home/archivos/mia/faseU/b18"
mkdir  -path~:~"/home/archivos/mia/faseU/b19"
mkdir  -path~:~"/home/archivos/mia/faseU/b20"
mkdir  -path~:~"/home/archivos/mia/faseU/b21"
mkdir  -path~:~"/home/archivos/mia/faseU/b22"
mkdir  -path~:~"/home/archivos/mia/faseU/b23"
mkdir  -path~:~"/home/archivos/mia/faseU/b24"
mkdir  -path~:~"/home/archivos/mia/faseU/b25"
mkdir  -path~:~"/home/archivos/mia/faseU/b26"
mkdir  -path~:~"/home/archivos/mia/faseU/b27"
mkdir  -path~:~"/home/archivos/mia/faseU/b28"
mkdir  -path~:~"/home/archivos/mia/faseU/b29"
mkdir  -path~:~"/home/archivos/mia/faseU/b30"
mkdir  -path~:~"/home/archivos/mia/faseU/b31"
mkdir  -path~:~"/home/archivos/mia/faseU/b32"
mkdir  -path~:~"/home/archivos/mia/faseU/b33"
mkdir  -path~:~"/home/archivos/mia/faseU/b34"
mkdir  -path~:~"/home/archivos/mia/faseU/b35"
mkdir  -path~:~"/home/archivos/mia/faseU/b36"
mkdir  -path~:~"/home/archivos/mia/faseU/b37"
mkdir  -path~:~"/home/archivos/mia/faseU/b38"
mkdir  -path~:~"/home/archivos/mia/faseU/b39"
mkdir  -path~:~"/home/archivos/mia/faseU/b40"
mkdir  -path~:~"/home/archivos/mia/faseU/b41"
mkdir  -path~:~"/home/archivos/mia/faseU/b42"
mkdir  -path~:~"/home/archivos/mia/faseU/b43"
mkdir  -path~:~"/home/archivos/mia/faseU/b44"
mkdir  -path~:~"/home/archivos/mia/faseU/b45"
mkdir  -path~:~"/home/archivos/mia/faseU/b46"
mkdir  -path~:~"/home/archivos/mia/faseU/b47"
mkdir  -path~:~"/home/archivos/mia/faseU/b48"
mkdir  -path~:~"/home/archivos/mia/faseU/b49"
mkdir  -path~:~"/home/archivos/mia/faseU/b50"

#reporte2 ::::(  )
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte2_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte2_vda1_tree.jpg" -name~:~tree

pause

#Reporte5 ::::(  )
#Ultimo reporte antes de la perdida
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/users.svg" -ruta~:~"/users.txt" -name~:~file
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/ls.pdf" -ruta~:~"/" -name~:~ls
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_tree.jpg" -name~:~tree
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_inode.pdf" -name~:~inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_block.pdf" -name~:~block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_bm_inode.pdf" -name~:~bm_inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_bm_block.pdf" -name~:~bm_block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte5_vda1_journaling.pdf" -name~:~journalinging
pause

#PERDIDA
#Loss -id~:~vda1

#reporte6 ::::(  )
#Reporte despues de la perdida es el 6
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_tree.jpg" -name~:~tree
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_inode.pdf" -name~:~inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_block.pdf" -name~:~block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_bm_inode.pdf" -name~:~bm_inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_bm_block.pdf" -name~:~bm_block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte6_vda1_journaling.pdf" -name~:~journaling
pause

#Recovery
#Recovery -id~:~vda1
#reporte7 ::::(  )
#Reporte despues del recovery es el 7
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_sb.pdf" -name~:~sb
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_tree.jpg" -name~:~tree
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_inode.pdf" -name~:~inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_block.pdf" -name~:~block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_bm_inode.pdf" -name~:~bm_inode
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_bm_block.pdf" -name~:~bm_block
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte7_vda1_journaling.pdf" -name~:~journaling
pause


#*************************************
#A PARTIR DE AQUI YA NO SON MINIMOS
#*************************************
#Renombrar
Login -pwd~:~123 -usr~:~root -id~:~vda1
ren -path~:~/home/a10 -name~:~ren10
ren -path~:~"/home/archivos/mia/z" -name~:~rename
logout
loGin -usr~:~user2 -pwd~:~user2 -id~:~vda1
#Este debe fallar por permisos de escritura
ren -path~:~"/home/b1.txt" -name~:~brenombre.txt
logoUt
#Pausa para el renombrar
pause

Login -pwd~:~123 -usr~:~root -id~:~vda1

#Indirectos dobles
mkfile -path~:~"/home/b2ble.txt" -size~:~18000
#Indirectos triples
mkfile -path~:~"/home/b3ple.txt" -size~:~280000
#Reporte 8
#rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte8_vda1_tree.jpg" -name~:~tree
pause

#Copiar
#Debe dar error porque destino no existe
#cp -path~:~/home/archivos/mia/carpeta3 -dest~:~/home/archivos/mia/yo/no/existo
#cp -path~:~/home/archivos/mia/carpeta3 -dest~:~/home/archivos/mia/carpeta2
#Copiar indirectos
#cp -path~:~/home/archivos/mia/faseU -dest~:~/home/archivos/mia/carpeta2
#Reporte 9
#rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte9_vda1_tree.jpg" -name~:~tree
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte9_vda1_tree.jpg" -ruta~:~"/" -name~:~ls
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte9_vda1_tree.jpg" -name~:~file
pause

#FIND
find -Path~:~"/" -name~:~*
pause
find -Path~:~"/" -name~:~"?.*"
#Debe dar error porque no exxiste path
find -Path~:~"/no/existo" -name~:~?
pause

#EDIT
edit -path~:~"/home/b3ple.txt" -size~:~50
edit -path~:~"/home/b2ble.txt" -size~:~280000
#Reporte 10
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte10_vda1_tree.jpg" -ruta~:~"/" -name~:~ls
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte10_vda1_tree.jpg" -name~:~file
#rep -id~:~vda1 -Path~:~"/home/archivos/reports2/reporte10_vda1_tree.jpg" -name~:~tree

#CAT
logout
Login -pwd~:~user2 -usr~:~user2 -id~:~vda1
#Escritura
cat -file2~:~/home/b1.txt -file1~:/users.txt
logout
Login -pwd~:~123 -usr~:~root -id~:~vda1
cat -file2~:~/home/b1.txt -file1~:/users.txt
Pause


#CHGRP
chgrp -usr~:~user1 -grp~:~"Compi 2"
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/usersCHGRP.svg" -ruta~:~"/users.txt" -name~:~file
logout
loGin -usr~:~user1 -pwd~:~user1 -id~:~vda1
#Debe marcar error porque no es root
chgrp -usr~:~user1 -grp~:~Archivos
logout
pause

#CHOWN
Login -pwd~:~123 -usr~:~root -id~:~vda1
chown -path~:~"/home/archivos/mia/faseU" -usr~:~user2 -R
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/lsCHOWN.pdf" -ruta~:~"/home/archivos/mia/faseU" -name~:~ls
pause

chmod -path~:~/ -ugo~:~000 -R
rep -id~:~vda1 -Path~:~"/home/archivos/reports2/lsULTIMO.pdf" -ruta~:~"/" -name~:~ls
pause


#FIN DE LA CALIFICACION :)(

