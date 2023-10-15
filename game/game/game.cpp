#include "Debug/game.tlog/libraries.h"
//Подключение файла с подключёнными библиотеками

using namespace std;

const int heightmap = 3; //Объщий размер карты по высоте
const int widthmap = 3;  //и ширине

int xmap = widthmap / 2; //Текущие координаты на карте
int ymap = heightmap / 2;//начальное значение равно середине карты

//класс "Игрок"
class Player
{
public:
	int xpalayer = 5; //положение игрока по x
	int ypalayer = 5; //положение игрока по y
					  //отчёт ведется от левого верхнего угла [0][0]
	//матод, возвращающий символ, которым обозначен игрок
	char getcharacter()
	{
		return character;
	}

	bool gameOver = false;

private:
	char character = '@'; //обозначение играка на карте
};

//Класс "Комната"
class Room
{
public:
	Room() //конструктор класса
	{
		this->room = new char* [height]; //объявление динамического массива, хранящеко каждый символ комнаты
		for (int i = 0; i < height; i++)
		{
			room[i] = new char[width];
		}
	}

	//матод вывода "комнаты" на экран
	void showRoom(Player pl1/*текущий игрок*/)
	{
		Room::bildRoom(pl1/*текущий игрок*/); //вызов матода постоения комнаты
		for (int i = 0; i < height; i++) //прокрутка по всем элементам массива
		{
			for (int j = 0; j < width; j++)
			{
				cout << this->room[i][j];
			}
			cout << endl;
		}
	}

	//матод проверки элемета массива
	//на нахождение в нём данного символа
	bool checkTile(int i/*y элемента*/, int j/*х элемента*/, char tile/*данный символ*/)
	{
		return room[i][j] == tile;
	}

	//матоды, возвращающие высоту и ширину комнаты
	static int getWidth()
	{
		return width;
	}
	static int getHeight()
	{
		return height;
	}

	//диструктор класс удаляющий динамический массив
	~Room()
	{
		for (int i = 0; i < width; i++)
		{
			delete[] room[i];
		}
		delete[] room;
	}

private:

	//матод построения комнаты
	void bildRoom(Player pl1)
	{
		for (int i = 0; i < height; i++) //цикл внешнего массива(Высота)
		{
			for (int j = 0; j < width; j++) //цикл массивов-элементов(Ширина)
			{
				if (i == 0 || i == height - 1) //если текущая "высота" максимальна или минимальна то...
				{
					//...присвоить текущему элемету символ стены
					this->room[i][j] = wall;
					if (i == 0 && j == width / 2 && ymap != 0) //если текущая "ширина" равна ширине комнаты/2 и эта комната не крайняя на карте то...
						//...присвоить текущему элемету символ вершней/нижней стены
						this->room[i][j] = dnupDoor;
					if (i == height-1 && j == width / 2 && ymap != heightmap - 1)
						this->room[i][j] = dnupDoor;
				}
				else if (j == 0 || j == width - 1) //если текущая "ширина" максимальна или минимальна то...
				{
					//...присвоить текущему элемету символ вершней/нижней стены
					this->room[i][j] = wall;
					if (j == 0 && i == height / 2 && xmap !=0) //если текущая "высота" равна высоте комнаты/2 и эта комната не крайняя на карте то...
						this->room[i][j] = rtltDoor;
					if (j == width-1 && i == height / 2 && xmap != widthmap-1)
						this->room[i][j] = rtltDoor;
				}
				else if (i == pl1.ypalayer && j == pl1.xpalayer)//если текущая "ширина" и "высота" равны координатам игрока то...
					//...присвоить текущему элемету символ игрока
					this->room[i][j] = pl1.getcharacter();
				else if (i == yrock && j == xrock)//генеращия каней в слечайном месте
					this->room[i][j] = wall;
				//в ином случае присвоить текущему элементу символ пола
				else
					this->room[i][j] = floor;
			}
		}
	}

	static const int width = 11; //ширина комнаты
	static const int height = 11; //высота комнаты
	char** room; //указатель на указатель типа char (объявление динамического двумерного массива)

	int xrock = rand() %6+2; //координаты камня по x...
	int yrock = rand() %6+2; //и y раные случайному числу в диапозоне от 2 до 8
	char dnupDoor = '-'; //вершняя и нижняя дверь
	char rtltDoor = '|'; //правая и левая двери
	char wall = '#'; //стена
	char floor = '.';//пол
};

//функция для управления игроком(изменения его кооридинат)
Player control(Player& otherpl/*текущий игрок*/, Room& test/*текущая комната*/, int& xmap/*координаты на карте х...*/, int& ymap/*...y*/)
{
	;
	char inp = _getch();
	switch (inp)
	{
	//если нажаты: 
	//клавиши 'w' или 'ц'
	case 'ц':
	case 'w':
		//если на пути движения игрока нет стены...
		if (!test.checkTile(otherpl.ypalayer - 1, otherpl.xpalayer, '#'))
		{
			//...то
			//если на пути движения игрока есть дверь(верхняя)
			if (test.checkTile(otherpl.ypalayer - 1, otherpl.xpalayer, '-'))
			{
				//изменить координыты игрока на карте на один выше по y
				ymap -= 1;
				//изменить координаты игрока(y) в комнате на максимальную высоту - 2
				otherpl.ypalayer = test.getHeight() - 2;
			}
			else // в ином случае изменить координаты игрока в комнате на 1 выше по y
				otherpl.ypalayer -= 1;
			return otherpl;
		}
		break;
		//дальше идёт тоже самое, только с другими значениями
		//поэтому я забил хуй на этот участок кода
	case 'ы':
	case 's':
		if (!test.checkTile(otherpl.ypalayer + 1, otherpl.xpalayer, '#'))
		{
			if (test.checkTile(otherpl.ypalayer + 1, otherpl.xpalayer, '-'))
			{
				ymap += 1;
				otherpl.ypalayer = 1;
			}
			else
				otherpl.ypalayer += 1;
			return otherpl;
		}
		break;
	case 'ф':
	case 'a':
		if (!test.checkTile(otherpl.ypalayer, otherpl.xpalayer - 1, '#'))
		{
			if (test.checkTile(otherpl.ypalayer, otherpl.xpalayer - 1, '|'))
			{
				xmap -= 1;
				otherpl.xpalayer = test.getWidth() - 2;
			}
			else
				otherpl.xpalayer -= 1;
			return otherpl;
		}
		break;
	case 'в':
	case 'd':
		if (!test.checkTile(otherpl.ypalayer, otherpl.xpalayer + 1, '#'))
		{
			if (test.checkTile(otherpl.ypalayer, otherpl.xpalayer + 1, '|'))
			{
				xmap += 1;
				otherpl.xpalayer = 1;
			}
			else
				otherpl.xpalayer += 1;
			return otherpl;
		}
		break;
	case '0':
		otherpl.gameOver = true;
		break;
	default:
		break;
	}
}

//основное тело программы
int main()
{

	srand(time(0)); //функция для генерации рандомных чисел
	Player player1; //создания игрока
	Room massOFroom[heightmap][widthmap]; //создание массива комнат(карты)

	//возможнось вводить русские символы
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(handle, FOREGROUND_RED);
	//установка зелёного цвета текста
	system("color 03");

	//бесконецный цикл
	for (;!player1.gameOver;)
	{
		//вызов метода вывода комнаты у текущий кумнаты из массив
		massOFroom[ymap][xmap].showRoom(player1);

		// координатпроверкаь комнаты(для отладки)
		cout << "x =" << xmap << endl;
		cout << "y =" << ymap << endl;
		cout << "0 =< y and x >=" << widthmap-1 << endl;
		cout << "press '0' to exit";
		//

		//вызов функции управления игроком
		//в неё передаётся текущий игрок, комната и кооридинаты на карте
		control(player1, massOFroom[ymap][xmap], xmap, ymap);
		Sleep(5);
		//отчистка экрана
		system("cls");

		//проверка, не выходят ли координаты на карте за максимальные или минимальные
		if (xmap > widthmap-1 || ymap > heightmap-1 || xmap < 0 || ymap < 0)
			//если да, то завершит программу с кодом 1
			return 1;
	}
	return 0;
}