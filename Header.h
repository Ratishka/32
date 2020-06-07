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

	bool IsEmpty();//�������� �� �������
	bool IsFull(); //�������� �� �������
	int GetVertexElement(int i) { return vertList[i]; }//�������� �������� �������                               
	vector<char> GetVertList() { return  vertList; }      //�������� ������ ������                        
	int GetMatrixElement(int i, int j) { return Matrix[i][j]; }//�������� ������� ������� ���������    
	int GetAmountEdges();//�������� ���������� �����                      
	int GetAmountVerts() { return vertList.size(); }//�������� ���������� ������                             
	int GetVertPos(const int& v);//�������� ����� �������		                                                                              
	void addVertex(const char&);
	void addEdge(const char& vertex1, const char& vertex2, int weight);
	void PrintGraph();                                           
	void DeleteVertex();                                          
	void DeleteEdge(const int& v1, const int& v2);               
	void drawGraph();                                      
};

extern Graph graph;
int** MatrTSP(); //��������� �������, ������� 0 �� -1
int* FindMin(int* l, int n);//����� ������������ �������� � ������ �������
int** ReductMatr(int** m); //�������� �������
int** RebuildMatr(int** m);
void CommiResult(int);//����� ���������� ������� ������ ������������
bool CommiCheck(int** matrix);//����� �� ������ ���� ������
int Circle_Check(int x, int y);//�������� �� ��������� ������� � �������
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
void Move(int x, int y);   //������������ ������                                                 
void Click(int button, int state, int x, int y);                       
void reshape(int w, int h);                               
void display();                     


