#pragma once

#include <glut.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct point {
	int x, y;
	point(int x1, int y1) {
		x = x1;
		y = y1;
	}
};

const int maxVerts = 6;
extern int WinW;
extern int WinH;

class Graph
{
private:
	vector<char> vertList;
	int Matrix[maxVerts][maxVerts];
public:
	Graph();
	~Graph();

	bool IsEmpty();//проверка на пустоту
	bool IsFull(); //проверка на полноту
	int GetVertexElement(int i) { return vertList[i]; }//получить значение вершины                               
	vector<char> GetVertList() { return  vertList; }      //получить вектор вершин                        
	int GetMatrixElement(int i, int j) { return Matrix[i][j]; }//получить элемент матрицы смежности    
	int GetAmountEdges();//получить количество ребер                      
	int GetAmountVerts() { return vertList.size(); }//получить количество вершин                             
	int GetVertPos(const int& v);//получить номер вершины		                                                                              
	void addVertex(const char&);
	void addEdge(const char& vertex1, const char& vertex2, int weight);
	void PrintGraph();                                           
	void DeleteVertex();                                          
	void DeleteEdge(const int& v1, const int& v2);               
	void drawGraph();                                      
};

extern Graph graph;
int** MatrTSP(); //создается матрица, заменяя 0 на -1
int* FindMin(int* l, int n);//поиск минимального элемента в строке матрицы
int** ReductMatr(int** m); //редукция матрицы
int** RebuildMatr(int** m);
void CommiResult(int);//вывод результата решения задачи Коммивояжера
bool CommiCheck(int** matrix);//может ли задача быть решена
int Circle_Check(int x, int y);//проверка на вхождение курсорв в вершину
void drawCircle(int x, int y, int R);
void drawText(int text, int, int);
void drawLine(int text, int x0, int y0, int x1, int y1);
void drawVertex(int n);                                                    
void Button1();
void Button2();
void Button3();
void Button4();
void Button5();
void makeGraph();                                                                                                                                                                                                    
void Move(int x, int y);   //передвижение вершин                                                 
void Click(int button, int state, int x, int y);                       
void reshape(int w, int h);                               
void display();                     


