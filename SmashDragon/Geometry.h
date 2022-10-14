/**********************************************************************************
// Geometry (Arquivo de Cabe�alho)
//
// Cria��o:     05 Oct 2007
// Atualiza��o: 07 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Agrupa a defini��o de todas as formas geom�tricas suportadas:
//              ponto, linha, ret�ngulo, c�rculo, pol�gono e mista (agrupamento
//              de uma ou mais geometrias)
//
**********************************************************************************/

#ifndef _PROGJOGOS_GEOMETRY_H_
#define _PROGJOGOS_GEOMETRY_H_

#include "Types.h"                                      // tipos da engine
#include <list>                                         // lista da STL
using std::list;                                        // usar list sem std::

// ---------------------------------------------------------------------------

enum GeometryTypes
{
    UNKNOWN_T,                                          // desconhecido
    POINT_T,                                            // ponto
    LINE_T,                                             // linha
    RECTANGLE_T,                                        // ret�ngulo
    CIRCLE_T,                                           // c�rculo
    POLYGON_T,                                          // pol�gono
    MIXED_T                                             // mista
};

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------

class Geometry
{
protected:
    float x, y;                                         // posi��o da geometria
    float scale;                                        // escala da geometria
    float rotation;                                     // rota��o da geometria
    uint type;                                          // tipo da geometria

public:
    Geometry();                                         // construtor
    virtual ~Geometry();                                // destrutor

    virtual float X() const                             // coordenada x da geometria
    { return x; }            
    
    virtual float Y() const                             // coordenada y da geometria
    { return y; }    

    
    virtual float Scale() const                         // retorna escala da geometria
    { return scale; }

    virtual float Rotation() const                      // retorna rota��o da geometria
    { return rotation; }

    virtual uint Type() const                           // retorna tipo 
    { return type; }        
    
    virtual void Translate(float dx, float dy)          // move a geometria pelo delta (dx,dy)
    { x += dx; y += dy; }

    virtual void Scale(float factor)                    // amplia/reduz geometria por um fator de escala
    { scale *= factor; }

    virtual void ScaleTo(float value)                   // ajusta escala para o valor indicado
    { scale = value; }

    virtual void Rotate(float angle)                    // rotaciona geometria por um �ngulo
    { rotation += angle; }

    virtual void RotateTo(float value)                  // ajusta a rota��o para o valor indicado
    { rotation = value; }

    virtual void MoveTo(float px, float py)             // move a geometria para a posi��o (px,py)
    { x = px; y = py; }
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
public:
    Point();                                            // construtor padr�o
    Point(float posX, float posY);                      // construtor usando pontos-flutuantes
    Point(int posX, int posY);                          // construtor usando inteiros
    
    float Distance(const Point & p) const;              // calcula a dist�ncia at� outro ponto
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
public:
    Point a, b;                                         // linha vai do ponto A ao ponto B
    
    Line();                                             // construtor padr�o
    Line(float x1, float y1, float x2, float y2);       // construtor usando pontos-flutuantes
    Line(Point& pa, Point& pb);                         // construtor usando pontos

    float Ax() const { return x + (a.X() * scale); }    // coordenadas do mundo do ponto A eixo x
    float Ay() const { return y + (a.Y() * scale); }    // coordenadas do mundo do ponto A eixo y
    float Bx() const { return x + (b.X() * scale); }    // coordenadas do mundo do ponto B eixo x
    float By() const { return y + (b.Y() * scale); }    // coordenadas do mundo do ponto B eixo y
};

// --------------------------------------------------------------------------
// Rect
// --------------------------------------------------------------------------

class Rect : public Geometry
{
public:
    float left;                                         // coordenada esquerda do ret�ngulo
    float top;                                          // coordenada superior do ret�ngulo
    float right;                                        // coordenada direita do ret�ngulo
    float bottom;                                       // coordenada inferior do ret�ngulo

    Rect();                                             // construtor padr�o
    Rect(float x1, float y1, float x2, float y2);       // construtor usando pontos-flutuantes
    Rect(Point& a, Point& b);                           // construtor usando pontos

    float Left() const   { return x + (left*scale);   } // coordenadas do mundo do menor valor do eixo x
    float Top() const    { return y + (top*scale);    } // coordenadas do mundo do menor valor do eixo y
    float Right() const  { return x + (right*scale);  } // coordenadas do mundo do maior valor do eixo x
    float Bottom() const { return y + (bottom*scale); } // coordenadas do mundo do maior valor do eixo y
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
private:
    float radius;                                       // raio do c�rculo

public:
    Circle();                                           // construtor padr�o
    Circle(float r);                                    // contrutor com raio

    float Radius() const { return radius * scale; }     // tamanho do raio
    float CenterX() const { return x; }                 // coordenadas do mundo do centro (eixo x)
    float CenterY() const { return y; }                 // coordenadas do mundo do centro (eixo y)
};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
public:
    uint      vertexCount;                              // n�mero de v�rtices 
    Point*    vertexList;                               // vetor de v�rtices do pol�gono

    Poly();                                             // construtor padr�o
    Poly(Point * vList, uint vCount);                   // construtor
    Poly(const Poly& p);                                // construtor de c�pia
    ~Poly();                                            // destructor

    const Poly& operator=(const Poly& p);               // operador de atribui��o
}; 

// --------------------------------------------------------------------------
// Mixed
// --------------------------------------------------------------------------

class Mixed : public Geometry
{
public:
    list<Geometry*> shapes;                             // lista de formas geom�tricas
    
    Mixed();                                            // construtor padr�o
    ~Mixed();                                           // destructor

    void Insert(Geometry * s);                          // insere geometria na lista
    void Remove(Geometry * s);                          // remove geometria da lista

    void Translate(float dx, float dy);                 // move a geometria pelo delta (dx,dy)
    void Scale(float factor);                           // amplia/reduz geometria por um fator de escala
    void ScaleTo(float value);                          // ajusta escala para o valor indicado
    void MoveTo(float px, float py);                    // move a geometria para a posi��o (px,py)
};

// --------------------------------------------------------------------------

#endif
