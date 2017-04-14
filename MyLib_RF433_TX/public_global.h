/*
 * public_global.h
 * Created: 07-04-2017
 * Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */


#ifndef PUBLIC_GLOBAL_H_
#define PUBLIC_GLOBAL_H_

#ifndef F_CPU
/* prevent compiler error by supplying a default */
# define F_CPU 8000000UL
#endif

#define TRUE            (1)
#define FALSE           (0)
#define INTERVALO(valor, min, max) (valor < max && valor > min)
#endif /* PUBLIC_GLOBAL_H_ */