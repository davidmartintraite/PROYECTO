#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

MYSQL *conn;
int err;
MYSQL_RES *ress;
MYSQL_ROW row;

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char pet[512];
	char res[512];
	
	char nombre[20];
	char contrasena[20];
	char mail[50];
	int puntos;
	char cons[80];
	char consid[80];
	
	conn = mysql_init(NULL);
	if (conn == NULL){
		printf("Error en la conexi￳n: %u %s \n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost","root", "mysql", "bd", 0, NULL,0);
	if (conn = NULL){
		printf("Error al iniciar la conexi￳n: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	if((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error al crear el socket");
	}
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(9080);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0){
		printf("Error bind");
	}
	if (listen(sock_listen,100)<0){
		printf("Error listen");
	}
	int i;
	for (i=0; i<40; i++){
		printf("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("fino\n");
		int x =0;
		
		while (x == 0){
			
			ret = read(sock_conn, pet, sizeof(pet));
			pet[ret]= '\0';
			
			printf("Peticion: %s\n", pet);
			
			char *p = strtok(pet, "/");
			int cod = atoi(p);
			p = strtok(NULL, "/");
			
			if(cod == 0){
				x =1;
			}
			if(cod == 1){
				strcpy(nombre, p);
				p = strtok(NULL, "/");
				strcpy(contrasena, p);
				p = strcpy(NULL, "/");
				strcpy(mail, p);
				printf("Codigo; %d, Nombre: %s, Contrase￱a: %s, Correo: %s\n", cod, nombre, contrasena, mail);
				
				sprintf(cons, "SELECT Jugador.NOMBRE FROM Jugador WHERE Jugador.NOMBRE ='%s'", nombre);
				
				err = mysql_query (conn, cons);
				if (err != 0){
					printf("Error al consultar");
					exit(1);
				}
				
				ress = mysql_store_result (conn);
				row = mysql_fetch_row(ress);
				
				if(row == NULL){
					strcpy(consid,"SELECT MAX(Jugador.ID) FROM Jugador");
					err = mysql_query (conn, consid);
					if (err != 0){
						printf("Error al consultar");
						exit(1);
					}
					ress = mysql_store_result(conn);
					row = mysql_fetch_row(ress);
					int idj = atoi(row[0])+1;
					char porfin[100];
					sprintf(porfin,"INSERT INTO Jugador(ID,NOMBRE,CONTRASE￑A,MAIL,PUNTOS) VALUES(%d,'%s','%s','%s',0)",idj,nombre,contrasena,mail);
					
					err = mysql_query (conn, porfin);
					if(err!=0){
						printf("Error al insertar datos");
						exit(1);
						sprintf(porfin, "NO REGISTRADO");
					}
					else{
						sprintf(porfin,"SI");
					}
				}
				else{
					sprintf(res,"NO REGISTRADO");
				}
			}
			
			if(cod==2){
				strcpy (nombre, p);
				p = strtok(NULL, "/");
				strcpy(contrasena, p);
				
				printf("Codigo: &d, Nombre: %s, Contrase￱a: %s\n",cod, nombre, contrasena);
				
				sprintf(cons, "SELECT Jugador.NOMBRE, Jugador.CONTRASE￑A FROM Jugador WHERE  Jugador.NOMBRE= '%s' AND Jugador.CONTRASE￑A = '%s'", nombre,contrasena);
				err = mysql_query(conn, cons);
				if (err !=0){
					printf("Errror al consultar %u %s\n",mysql_errno(conn), mysql_error(conn));
					exit(1);
				}
				
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if(row == NULL){
					sprintf(res,"INCORRECTO");
				}
				else{
					sprintf("SI");
				}
			}
			
			if(cod ==3){
				prinf ("Codigo: %d", cod);
				sprintf(cons, "SELECT Jugador.NOMBRE FROM Jugador WHERE Jugador.PUNTOS = MAX(Jugador.PUNTOS)");
				
				err = mysql_query(conn,cons);
				if(err != 0){
					prinf("Error al consultar");
					exit(1);
				}
				res = mysql_store_result(conn, cons);
				row = mysql_fetch_row(res);
				if (row == NULL){
					printf("No va");
				}
				else{
					sprintf(res,"%s",row[0]);
				}
			}
			
			if(cod !=0){
				printf("Respuesta: %s \n", res);
				write(sock_conn,res,strlen(res));
			}
		}
		//close(sock_conn);
	}}
	//close(sock_conn);

