#ifndef CONSTANTES_H
#define CONSTANTES_H 
#include "geometria.h"
#include "imagen/gestor.h"

const int CICLO_ACELERACION = 10;
const int FPS = 10;

const int jugador_x = 16;
const int jugador_y = 24;

const char BFAireIzq[] = "renders/ballon2.bmp";
const char BFParadoIzq[] = "renders/ballon5.bmp";
const char BFPasoIzq[] = "renders/ballon6.bmp";
const char BFPasoDer[] = "renders/ballon8.bmp";
const char BFParadoDer[] = "renders/ballon7.bmp";
const char BFAireDer[] = "renders/ballon4.bmp";
const char BFSaltoIzq[] = "renders/ballon1.bmp";
const char BFSaltoDer[] = "renders/ballon3.bmp";
const char piedrarender[] = "renders/piedra.bmp";

const Color fondo_renders = Color::blanco;

const _2D::Punto v_mov(3,0);
const _2D::Punto v_salto(0,5);
const _2D::Punto v_grav(0,-1);
const _2D::Punto v_friccion(3,3);
const _2D::Punto v_piedrai(-10,0);
const _2D::Punto v_piedrad(10,0);

const Color ColorMuros = Color::blanco;
const Color ColorPuertasAbierta = Color::cafe;
const Color ColorPuertasCerrada = Color::gris(100);
const Color ColorBoton = Color::rojo;
const Color ColorHelices = Color::azul;
const Color ColorPortal = Color::verde;
const Color ColorPortalGrande = Color::magenta;
const Color ColorMeta = Color::amarillo;

const int delay = 40;
const int delayPiedra = 350;
const int IZQUIERDA  = 0;
const int DERECHA = 1;

GestorImagenes renders = GestorImagenes();
#endif