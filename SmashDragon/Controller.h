/**********************************************************************************
// Controller (Arquivo de Cabe�alho)
// 
// Cria��o:     09 Nov 2011
// Atualiza��o: 05 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Faz a leitura de controles
//
**********************************************************************************/

#ifndef _PROGJOGOS_CONTROLLER_H_
#define _PROGJOGOS_CONTROLLER_H_

// ---------------------------------------------------------------------------------

#define INITGUID                                // inclus�o dos GUIDs do DirectX
#define DIRECTINPUT_VERSION 0x0800              // usa vers�o 8 do DirectInput

// ---------------------------------------------------------------------------------

#include <dinput.h>                             // direct input
#include <xinput.h>                             // xinput
#include <list>                                 // listas da STL
#include <string>                               // strings da STL
using std::list;                                // usando listas sem std::
using std::string;                              // usando strings sem std::

// ---------------------------------------------------------------------------------

// eixos e bot�es do controle do Xbox
enum XboxCtrl
{
    DpadUp, DpadDown, DpadLeft, DpadRight,      // Dpad
    ButtonStart, ButtonBack,                    // Bot�es de menu
    LeftThumb, RightThumb,                      // Bot�es dos anal�gicos
    LeftBumper, RightBumper,                    // Bot�es LB e RB
    ButtonA, ButtonB, ButtonX, ButtonY,         // Bot�es A, B, X e Y
    LeftTrigger, RightTrigger,                  // Gatilhos LT e RT (faixa entre 0 e 255)
    ThumbLX, ThumbLY, ThumbRX, ThumbRY          // Eixos dos anal�gicos (faixa entre -32768 e 32767)
};

// n�mero do jogador no controle do Xbox
enum XboxPlayer
{
    PLAYER1,
    PLAYER2,
    PLAYER3,
    PLAYER4
};

// eixos do controle 
enum JoyAxis 
{
    AxisX,                                      // Eixo X
    AxisY,                                      // Eixo Y
    AxisZ,                                      // Eixo Z
    AxisRX,                                     // Eixo RX
    AxisRY,                                     // Eixo RY
    AxisRZ                                      // Eixo RZ
};

// informa��es do controle 
struct JoyInfo 
{
    GUID   guid;                                // identificador global �nico
    string name;                                // nome do controle
};

// partes do controle 
struct JoyPart 
{
    GUID   guid;                                // identificador global �nico
    DWORD  type;                                // tipo da parte
    string name;                                // nome da parte
};

// ---------------------------------------------------------------------------------

class Controller
{
private:
    LPDIRECTINPUT8 dInput;                      // objeto direct input
    LPDIRECTINPUTDEVICE8 joyDev;                // dispositivo do controle
    DIJOYSTATE joyState;                        // estado do controle
    XINPUT_STATE xboxState;                     // estado do controle do Xbox
    XINPUT_VIBRATION vibration;                 // vibra��o do controle do Xbox
    bool joyCtrl[32];                           // estado de libera��o de bot�es

    list<JoyPart> parts;                        // lista de bot�es e eixos para o controle selecionado
    list<JoyInfo> controllers;                  // lista dos dispositivos de controle    
    list<JoyInfo>::const_iterator selected;     // aponta para o controle selecionado

public:
    Controller();                               // construtor
    ~Controller();                              // destrutor

    bool Initialize();                          // inicializa controle
    bool XboxInitialize(int ctrl = 0);          // inicializa controle do Xbox
    
    bool UpdateState();                         // atualiza estado do controle
    bool XboxUpdateState(int ctrl = 0);         // atualiza estado do controle do Xbox
    
    bool ButtonDown(int button);                // verifica se um bot�o do controle est� pressionado
    bool ButtonUp(int button);                  // verifica se um bot�o do controle est� liberado
    bool ButtonPress(int button);               // registra novo pressionamento somente ap�s libera��o
    long Axis(int axis);                        // retorna o movimento de um eixo do controle
    long Slider(int slider);                    // retorna movimento do slider
    long Dpad(int pov = 0);                     // retorna o movimento do D-pad

    bool DeviceNext();                          // seleciona o pr�ximo controle da lista
    bool DevicePrev();                          // seleciona o controle anterior da lista
    const string * DeviceName();                // retorna o nome do controle selecionado
    list<JoyPart> & DeviceParts();              // retorna lista de bot�es e eixos do controle

    int XboxButton(int button);                 // retorna estado do bot�o do controle do Xbox
    int XboxTrigger(int trigger);               // retorna valor dos gatilhos do contole do Xbox
    int XboxAnalog(int stick);                  // retorna valor dos direcionais do controle do Xbox
    void XboxVibrate(int ctrl = 0,              // faz o controle do xbox vibrar
        int left = 65535, 
        int right = 65535);                    
};

// -------------------------------------------------------------------------------
// fun��es membro inline

// verifica se o bot�o do controle est� pressionado
inline bool Controller::ButtonDown(int button)
{ return joyState.rgbButtons[button] && 0x80; }

// verifica se o bot�o do controle est� pressionado
inline bool Controller::ButtonUp(int button)
{ return !(joyState.rgbButtons[button] && 0x80); }

// retorna o nome do controle selecionado
inline const string * Controller::DeviceName() 
{ return &(*selected).name; }

// retorna lista de bot�es e eixos do controle 
inline list<JoyPart> & Controller::DeviceParts() 
{ return parts;}

// ---------------------------------------------------------------------------------

// fun��o callback que enumera os controles
BOOL CALLBACK EnumerateControllers(LPCDIDEVICEINSTANCE lpDDi, LPVOID data);

// fun��o callback que enumera os bot�es e eixos do controle
BOOL CALLBACK EnumControllerParts(LPCDIDEVICEOBJECTINSTANCE lpDIdoi, LPVOID data);

// ---------------------------------------------------------------------------------

#endif