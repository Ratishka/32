#include "Header.h"
#include <glut.h>

Graph graph;
vector<point> coords;

using namespace std;
int MovVert;//перемещаемая вершина
int CursorX;//позиция курсора 
int CursorY;
bool* cursinVert = new bool[maxVerts]; //курсор на вершине
bool MovMode = false; //перемещены ли вершины
bool IsMove = false; //отвечает за перемещение вершин 

vector<pair<int, int>> PathVert;
vector<int> WayVert;
int R=50;

int WinW = 800;
int WinH = 600;
Graph::Graph()
{
	for (int i = 0; i < maxVerts; i++)
	{
		for (int j = 0; j < maxVerts; j++)
			Matrix[i][j] = 0;
	}
}

Graph::~Graph()
{ }

int Graph::GetVertPos(const int& vertex)
{
	for (size_t i = 0; i < vertList.size(); i++)
	{
		if (vertList[i] == vertex)
			return i;
	}
	return -1;
}

bool Graph::IsEmpty()
{
	if (vertList.size() != 0)
		return false;
	else
		return true;
}

bool Graph::IsFull()
{
	return (vertList.size() == maxVerts);
}

void Graph::DeleteVertex()
{
	if (IsEmpty())
	{
		cout << "\nГраф пуст\n";
		return;
	}
	int n = vertList.size();
	for (int j = 0; j < n; j++)
	{
		Matrix[n - 1][j] = 0;
		Matrix[j][n - 1] = 0;
	}

	vertList.pop_back();
	coords.pop_back();
}

void Graph::DeleteEdge(const int& vertex1, const int& vertex2)
{
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))	//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);							//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (Matrix[vertPos1][vertPos2] == 0 && Matrix[vertPos2][vertPos1] == 0)//если между ними уже есть ребро
		{
			cout << "Здесь ребра нет" << endl;
			return;
		}
		else														//иначе добавляем ребро
			Matrix[vertPos1][vertPos2] = 0;
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

int Graph::GetAmountEdges()
{
	int edges = 0;
	for (int i = 0; i < vertList.size(); i++)
		for (int j = 0; j < vertList.size(); j++)
			if (Matrix[i][j] > 0)
				edges++;
	return edges;
}
void Graph::addVertex(const char& vertex)
{
		vertList.push_back(vertex);
}

void Graph::addEdge(const char& vertex1, const char& vertex2, int weight)
{
	if (weight < 1)
	{
		cout << "\nДанная величина веса некорректна\n";
		return;
	}
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))
	{
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (Matrix[vertPos1][vertPos2] != 0 && Matrix[vertPos2][vertPos1] != 0)
		{
			cout << "Ребро между вершинами уже существует " << endl;
		}
		else
		{
			Matrix[vertPos1][vertPos2] = weight;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
	}
}
void Graph::drawGraph()
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = Matrix[i][j];
			if (a != 0)
				drawLine(a, coords[i].x, coords[i].y, coords[j].x, coords[j].y);
			if (a == Matrix[j][i] && a != 0)
				drawLine(a, coords[j].x, coords[j].y, coords[i].x, coords[i].y);
		}
	}
	drawVertex(n);
	glutPostRedisplay();
}

void Graph::PrintGraph()
{
	if (!IsEmpty())
	{
		cout << "Матрица смежности графа: " << endl;
		for (int i = 0; i < vertList.size(); i++)
		{
			cout << vertList[i] << " ";
			for (int j = 0; j < vertList.size(); j++)
				cout << setw(4) << Matrix[i][j];
			cout << endl;
		}
	}
	else
		cout << "Граф пуст " << endl;
}

void drawCircle(int x1, int y1, int R)
{
	float x, y;

	glColor4f(0, 0.255, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (int j = 1; j <= R; j++) {
		for (int t = 0; t <= 360; t++) {
			x = j * sin(t) + x1;
			y = j * cos(t) + y1;
			glVertex2f(x, y);
		}
	}
	glEnd();

}

void drawText(int t, int x1, int y1)
{
	string text = to_string(t);
	glColor3f(256, 256, 0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < text.length(); j++)
		glutBitmapCharacter(font, text[j]);
}

void drawLine(int text, int x0, int y0, int x1, int y1) 
{
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + R * vx;
	y1 = y1 + R * vy;

	glColor3i(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}

void drawVertex(int n)
{
	for (int i = 0; i < n; i++)
	{
		drawCircle(coords[i].x, coords[i].y, R);
		drawText(i + 1, coords[i].x, coords[i].y);
	}
}


void makeGraph()
{
	for (int i = 0; i < maxVerts; i++)
		cursinVert[i] = false;
	point p1(100,300), p2(350,250), p3(550,400), p4(450,50), p5(250,500), p6(700,150);
	coords.push_back(p1);
	coords.push_back(p2);
	coords.push_back(p3);
	coords.push_back(p4);
	coords.push_back(p5);
	coords.push_back(p6);

	graph.addVertex('1');
	graph.addVertex('2');
	graph.addVertex('3');
	graph.addVertex('4');
	graph.addVertex('5');
	graph.addVertex('6');

	graph.addEdge('1', '5', 8);
	graph.addEdge('1', '2', 4);
	graph.addEdge('5', '2', 23);
	graph.addEdge('5', '3', 12);
	graph.addEdge('3', '5', 12);
	graph.addEdge('2', '3', 15);
	graph.addEdge('3', '2', 15);
	graph.addEdge('2', '4', 9);
	graph.addEdge('4', '6', 11);
	graph.addEdge('6', '3', 6);
	graph.addEdge('5', '1', 8);
	graph.PrintGraph();
}

int** MatrTSP()
{
	int n = graph.GetAmountVerts();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int elem = graph.GetMatrixElement(i, j);
			if (elem == 0 or i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}
	}
	return matrix;
}

int* FindMin(int* line, int n)
{
	int min = 1000000;
	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];
	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;
	return line;
}

int** ReductMatr(int** pmatrix)
{
	int** matrix = pmatrix;
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
		matrix[i] = FindMin(matrix[i], n);
	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];
		}
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0)
				matrix[j][i] -= min;
		}
	}
	return matrix;
}

int** RebuildMatr(int** oldmatrix)
{
	int n = graph.GetAmountVerts();
	int** matrix = ReductMatr(oldmatrix);
	int max = -1;
	int line=0, column=0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];
				}
				for (int k = 0; k < n; k++)
				{
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];
				}
				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}
	}

	pair<int, int> p;
	p.first = line + 1;
	p.second = column + 1;
	PathVert.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}
	return matrix;
}

void CommiResult(int n)
{
	graph.PrintGraph();
	int second = PathVert[0].second;
	int i = 2;
	WayVert.push_back(PathVert[0].first);
	WayVert.push_back(PathVert[0].second);
	while (i != graph.GetAmountVerts() + 1)
		for (int j = 1; j < graph.GetAmountVerts(); j++)
			if (PathVert[j].first == second)
			{
				second = PathVert[j].second;
				WayVert.push_back(second);
				i++;
			}
	WayVert.pop_back();
	cout << "Ответ: ";
	int j = 0;
	for (int i = 0; i < WayVert.size(); i++)
	{
		if (WayVert[i] == n)
			j = i;
	}
	for (int i = 0; i < WayVert.size() + 1; i++)
	{
		cout << WayVert[j % WayVert.size()];
		if (i != WayVert.size())
			cout << " -> ";
		j++;
	}
	int sum = 0;
	for (int i = 0; i < PathVert.size(); i++)
	{
		int line = PathVert[i].first - 1;
		int column = PathVert[i].second - 1;
		sum += graph.GetMatrixElement(line, column);
	}
	cout << "\n Длина пути:  " << sum << endl;
}

bool CommiCheck(int** matrix)
{
	if (graph.IsEmpty())
		return false;
	for (int i = 0; i < graph.GetAmountVerts(); i++)
	{
		int cnt = 0;
		for (int j = 0; j < graph.GetAmountVerts(); j++)
		{
			if (matrix[i][j] > 0)
				cnt++;			
		}
		if (cnt < 1)
		return false;
		
	}
	return true;
}

int Circle_Check(int x, int y)
{
	for (int i = 0; i < graph.GetAmountVerts(); i++)
		if (pow(x - coords[i].x, 2) + pow(y - coords[i].y, 2) <= R * R)
			return i;
	return -1;
}

void Move(int x, int y)//отслеживание движения мыши
{
	y = WinH - y;
	CursorX = x;
	CursorY = y;
	int i = Circle_Check(x, y);
	if (i != -1)
		cursinVert[i] = true;
	else
		for (int j = 0; j < graph.GetAmountVerts(); j++)
			cursinVert[j] = false;
	if (IsMove)
	{
		coords[MovVert].x = CursorX;
		coords[MovVert].y = CursorY;
	}
	glutPostRedisplay();
}
void Button1()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(20, WinH - 20);
	glVertex2i(20, WinH - 80);
	glVertex2i(100, WinH - 80);
	glVertex2i(100, WinH - 20);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	string name = "Salesman";
	glRasterPos2i(30, WinH-50);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button2()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(WinW - 20, WinH - 20);
	glVertex2i(WinW - 20, WinH - 80);
	glVertex2i(WinW - 100, WinH - 80);
	glVertex2i(WinW - 100, WinH - 20);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	string name = "Add Vertex";
	glRasterPos2i(WinW - 90, WinH-50);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button3()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(WinW - 20, WinH - 100);
	glVertex2i(WinW - 20, WinH - 160);
	glVertex2i(WinW - 100, WinH - 160);
	glVertex2i(WinW - 100, WinH - 100);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	string name = "Del Vertex";
	glRasterPos2i(WinW - 90, WinH - 130);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button4()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(WinW - 20, WinH - 180);
	glVertex2i(WinW - 20, WinH - 240);
	glVertex2i(WinW - 100, WinH - 240);
	glVertex2i(WinW - 100, WinH - 180);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	string name = "Add Edge";
	glRasterPos2i(WinW - 90, WinH - 210);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button5()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(WinW - 20, WinH - 260);
	glVertex2i(WinW - 20, WinH - 320);
	glVertex2i(WinW - 100, WinH - 320);
	glVertex2i(WinW - 100, WinH - 260);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	string name = "Delete Edge";
	glRasterPos2i(WinW - 90, WinH - 290);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}
void Click(int button, int state, int x, int y)//действия с кнопками 
{
	int j = Circle_Check(x, WinH - y);
	if (IsMove)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			IsMove = false;
			return;
		}
	}
	if (j != -1)
	{
		MovMode = true;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			IsMove = true;
			MovVert = j;
			return;
		}
	}
	if (x >= 20 && x <= 100 && y >= 20 && y <= 80)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int num;
			WayVert.clear();
			PathVert.clear();
			graph.PrintGraph();
			cout << "Введите вершину, с которой начать обход: ";
			cin >> num;
			cout << endl;
			cout << "Решение задачи коммивояжера\n";
			int** matrix = MatrTSP();
			bool tsp = CommiCheck(matrix);
			if (!tsp)
			{
				cout << "\nЗадача Коммивояжера не может быть решена\n\n";
				return;
			}
			int n = graph.GetAmountVerts();
			while (PathVert.size() < n)
				matrix = RebuildMatr(matrix);
			cout << endl;
			CommiResult(num);
			return;
		}
	}

	if (x >= WinW - 100 && x <= WinW - 20 && y <= 80 && y >= 20)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int c = graph.GetAmountVerts();
			if (!graph.IsFull())
			{
				char v = c + '1';
				graph.addVertex(c + '1');
				point m(WinW / 2, WinH / 2);
				coords.push_back(m);
				cout << "\nДобавлена вершина: " << c + 1 << endl;
			}
			else cout << "\nДостигнуто максимальное количество вершин. " << endl;
		}
	}

	if (x >= WinW - 100 && x <= WinW - 20 && y <= 160 && y >= 100)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			graph.DeleteVertex();
			int c = graph.GetAmountVerts();
			cout << "\nУдалена вершина: " << c + 1<< endl;
			return;
		}
	}

	if (x >= WinW - 100 && x <= WinW - 20 && y >= 180 and y <= 240)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			char startVertex, endVertex;
			int edgeWeight, vertNum;
			cout << "Количество добавляемых ребер: "; cin >> vertNum;
			for (int i = 0; i < vertNum; i++)
			{
				cout << "Исходная вершина: "; cin >> startVertex;
				cout << "Конечная вершина: "; cin >> endVertex;
				cout << "Вес ребра: "; cin >> edgeWeight;
				graph.addEdge(startVertex, endVertex, edgeWeight);
			}
			return;
		}
	}
	if (x >= WinW - 100 && x <= WinW - 20 && y >= 260 && y <=320)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			char startVertex, endVertex;
			cout << "Исходная вершина: "; cin >> startVertex;
			cout << "Конечная вершина: "; cin >> endVertex;
			graph.DeleteEdge(startVertex, endVertex);
			return;
		}
	}
	
}

void reshape(int w, int h)
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.drawGraph();
	Button1();
	Button2();
	Button3();
	Button4();
	Button5();

	glutSwapBuffers();
}