#include <QWidget>
#include <fstream>
#include <QGridLayout>
#include "map.h"
#include <QDebug>
using namespace std;

int cityCount;
int routeCount;
int seq;
int customer[15][MAXN];
QDateTime dateTime;
Route route[50];

Block::Block(QWidget *parent) :
    QLabel(parent)
{
    No = -1;
    isCity = false;    
    setPixmap(QPixmap(":/images/0"));  
}

void Block::setting(int N, int isCit)
{
    No = N;
    if(isCit)
	isCity = true;
    setPixmap(QPixmap(":/images/" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
}

OneTrip::OneTrip(int seqq)
{
    number = seqq;
    routeSeq = 0;
    position = -1;
}
void OneTrip::run()
{
    /*
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(routeUpdate()));
    */
    qDebug() << "THREAD\n" ;
    int i;
    for(;customer[number][routeSeq] != -1; routeSeq ++)
    {
	switch(route[customer[number][routeSeq]].kind)
	{
	case AIR:
	    for(i = 0; i < route[customer[number][routeSeq]].dist; i ++)
	    {
		position = route[customer[number][routeSeq]].step[i];
		sleep(100);
	    }
	    break;
	case RAIL:
	    for(i = 0; i < route[customer[number][routeSeq]].dist; i ++)
	    {
		position = route[customer[number][routeSeq]].step[i];
		sleep(200);
	    }
	    break;
	case ROAD:
	    for(i = 0; i < route[customer[number][routeSeq]].dist; i ++)
	    {
		position = route[customer[number][routeSeq]].step[i];
		sleep(300);
	    }
	    break;
	}
    }
//    delete timer;
    
}

    
int loadMap(Block* blocks, Route* route, int row, int column)
{
    char temp[40];
    int i, j, k, l, m, s;
    int n = 0;
    ifstream input ("map.dat");
    if(input.is_open())
    {
	input >> temp;
	input >> n;
	cityCount = n;
	for(k = 0; k < n; k ++)
	{
	    input >> temp;
	    input >> m;
	    input >> temp;
	    input >> s;
	    input >> temp;
	    input >> i;
	    input.ignore();
	    input >> j;
	    //处理block的i和j问题
	    blocks[i * row + j].setting(m, 1);

	    input >> temp;
	    for(l = 1; l < s; l ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		//处理block
		blocks[i * row + j].setting(m, 0);
	    }
	}


	input >> temp;
	input >> m;
	routeCount = m;
	for(k = 0; k < m; k ++)
	{
	    input >> temp;
	    input >> l;
	    route[k].startCity = l;
	    input >> temp;
	    input >> l;
	    route[k].endCity = l;
	    input >> temp;
	    input >> l;
	    route[k].kind = (unsigned char)l;
	    input >> temp;
	    input >> l;
	    route[k].price = l;
	    input >> temp;
	    input >> l;
	    route[k].dist = l;
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].begin.setHMS(i, j, 0);
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].end.setHMS(i, j, 0);
	    input >> temp;
	    for(s = 0; s < route[k].dist; s ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		route[k].step[s] = i * COLUMN + COLUMN;
	    }
	}	
	input.close();
    }
    return n;
}

int test(Block* blocks, Route* route, int row, int column)
{
    //未完，用于测试
    int i, j, k, n, m;
    n = 2;
    cityCount = n;
    blocks[0].setting(0, 1);
    blocks[1].setting(0, 0);
    blocks[1 * column + 0].setting(1, 0);
    blocks[1 * column + 1].setting(1, 1);

    m = 2;
    routeCount = m;
    route[0].startCity = 0;
    route[0].endCity = 1;
    route[0].kind = 1;
    route[0].price = 100;
    route[0].dist = 1;
    route[0].begin.setHMS(6, 0, 0);
    route[0].end.setHMS(6, 5, 0);
    route[0].step[0] = 1 * COLUMN + 1;
        
    route[1].startCity = 1;
    route[1].endCity = 0;
    route[1].kind = 2;
    route[1].price = 50;
    route[1].dist = 2;
    route[1].begin.setHMS(7, 0, 0);
    route[1].end.setHMS(7, 20, 0);
    route[1].step[0] = 0 * COLUMN + 1;
    route[1].step[1] = 0;
    
    return n;
}
