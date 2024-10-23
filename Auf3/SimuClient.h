#pragma once
#pragma warning (disable:4786)
#include <string>

#define SIMUCLIENT_API 
//#define _WIN32_WINNT 0x0502
#define USE_GENERIC_BUT_CPU_INTENSIVE_SLEEP 0

// NUTZBARE FUNKTIONEN (offizielle Schnittstelle)
/* 
使用地址与图形服务器建立连接，并根据窗口大小 X 和 Y 确定窗口的大小。
示例: bInitialisiereGrafik(800,500);
*/
SIMUCLIENT_API bool bInitialisiereGrafik(int iFenstergroesseX, int iFenstergroesseY, const char* adresse = "127.0.0.1", const char* port = "7654");

/**
 * @brief 在坐标 X 和 Y 处绘制一个十字路口
 * @param koordinateX
 * @param koordinateY
 * @return
 */
SIMUCLIENT_API bool bZeichneKreuzung(int koordinateX, int koordinateY);

/* 
绘制一条具有往返路径的街道，指定长度。街道由一系列点生成。
至少需要 2 个点（直线）。坐标的数量总是成对出现（X/Y）。
示例:	
int feld[] = { 100 , 200 , 300 , 400 }; 
int anzahl = 2;
bZeichneStrasse("Hin", "Rueck", 40, anzahl, feld);
*/
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

/*
	在指定的路线上显示一辆汽车。RelPosition 是相对于路线长度的位置（值介于 0 和 1 之间）。
	bZeichnePKW("Rennauto", "Rennstrecke" , AbschnittStrecke / WegLaenge, 250, 80);
}
*/
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

/*
	在指定的路线上显示一辆自行车。RelPosition 是相对于路径长度的位置（值介于 0 和 1 之间）。

	bZeichneFahrrad("Drahtesel", "Fahrradstrasse" , AbschnittStrecke / WegLaenge, 15);
*/
SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

/*
与图形服务器断开连接并关闭窗口
*/
SIMUCLIENT_API void vBeendeGrafik();

/* 将指定的车辆从图形应用程序中移除 */
SIMUCLIENT_API bool bLoescheFahrzeug(const std::string& name);

/* 在输出窗口的标题栏中显示全局时间
*/
SIMUCLIENT_API void vSetzeZeit(const double globaleZeit);

// Wrapperfunktion fuer Sleep
/*
	程序执行将延迟指定的毫秒数。
*/
SIMUCLIENT_API void vSleep(int anzahlMillisekunden);


SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

SIMUCLIENT_API bool bLoescheFahrzeug(const char* name);
