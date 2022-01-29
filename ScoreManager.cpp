#include "Headers.h"
#include "Externs.h"
GLfloat ScoreManager::scoreX = 480, ScoreManager::scoreY = 550;
GLint ScoreManager::score, ScoreManager::totalR;
string ScoreManager::name;	// Name of player
ScoreManager::ScoreManager()
{
	score = 0;
	totalR = 0;
	scoreX = 600;
	scoreY = 550;
}
string ScoreManager::getName()
{
	return name;
}
void ScoreManager::reset()
{
	score = 0;
}
void ScoreManager::init()
{
	score = 0;
} 
void ScoreManager::increase()
{
	score += 10;
}
void ScoreManager::draw()
{
	DrawManager::setColor(YELLOW, 0.7);
	DrawManager::rectangle(WindowManager::getWidth() - 250.0f, WindowManager::getHeight() - 240.0f, 250.0f, 240.0f);

	char temp[40];
	snprintf(temp, 40, "SCORE :  %d", score);
	DrawManager::setColor(RED);
	TextManager::render(WindowManager::getWidth() - 200.0f, WindowManager::getHeight() - 50.0f, temp);
}
void ScoreManager::drawGameOver()
{
	char temp[40];

	// Draw Score
	snprintf(temp, 40, "SCORE : %d", score);
	DrawManager::setColor(BLACK);
	TextManager::render(WindowManager::getWidth() / 2.0f - 530, WindowManager::getHeight() - 300.0f, temp);

	// Draw name entry
	glPushMatrix();
	glTranslatef(WindowManager::getWidth() / 2.0f - 630, WindowManager::getHeight() / 2.0f - 30, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);
	DrawManager::setColor(BLACK);
	TextManager::render(0, 0, name);
	glPopMatrix();
}

void ScoreManager::drawBoard()
{
	FILE* hs;
	char name[40], S[10];
	GLfloat T;
	int i;
	hs = fopen("Data\\HighScore.txt", "r");
	menu.hsImage.render(460, 400);

	DrawManager::setColor(166, 41, 166);
	TextManager::render(scoreX, scoreY, "POS", 1.3);
	TextManager::render(scoreX + 130, scoreY, "NAME",1.3);
	TextManager::render(scoreX + 630, scoreY, "TIME", 1.3);
	TextManager::render(scoreX + 820, scoreY, "SCORE", 1.3);


	DrawManager::setColor(255, 255, 255);
	for (i = 0; EOF != fscanf(hs, "%s %f %s\n", name, &T , S); i++)
	{
		char Temp[5];
		sprintf(Temp, "%02d", i + 1);
		TextManager::render(scoreX + 25, scoreY - 70 - 50 * i, Temp, 1);
		TextManager::render(scoreX + 130, scoreY - 70 - 50 * i, name,1);
		sprintf(Temp, "%02d", int((T / 70) / 3600));
		TextManager::render(scoreX + 600, scoreY - 70 - 50 * i, Temp,1);
		TextManager::render(scoreX + 650, scoreY - 70 + 2 - 50 * i, ":",1);
		sprintf(Temp, "%02d", int(fmod(((T / 70) / 60), 60)));
		TextManager::render(scoreX + 665, scoreY - 70 - 50 * i, Temp, 1);
		TextManager::render(scoreX + 715, scoreY - 70 + 2 - 50 * i, ":", 1);
		sprintf(Temp, "%02d", int(fmod((T / 70), 60)));
		TextManager::render(scoreX + 730, scoreY - 70 - 50 * i, Temp,1);
		TextManager::render(scoreX + 840, scoreY - 70 - 50 * i, S, 1);
	}


	fclose(hs);
	//iDrawBack();
}

struct ScoreType
{
	string name;
	GLfloat time;
	GLint score;
};
void read(vector<ScoreType>& scoreSheet)
{
	ifstream in;
	in.open("Data\\Highscore.txt", ios::in);
	while (!in.eof())
	{
		string str;
		GLint s;
		GLfloat t;
		in >> str >> t >> s;
		if (str != "")
		{
			scoreSheet.push_back({ str, t , s });
		}
	}
	in.close();
}
void write(vector<ScoreType>& scoreSheet)
{
	GLint i;
	ofstream out;
	out.open("Data\\Highscore.txt", ios::out);
	for (i = 0; i < scoreSheet.size() - 1 && i < 9; i++)
	{
		out << scoreSheet[i].name << " " << scoreSheet[i].time << " " << scoreSheet[i].score << endl;
	}
	out << scoreSheet[i].name << " " << scoreSheet[i].time << " " << scoreSheet[i].score;
	out.close();
}
void ScoreManager::save()
{
	vector<ScoreType> scoreSheet;
	read(scoreSheet);
	ScoreType temp = { name, GameManager::getTime() , score };
	GLint i;
	for (i = 0; i < scoreSheet.size(); i++)
	{
		if (score > scoreSheet[i].score)
		{
			scoreSheet.insert(scoreSheet.begin() + i, temp);
			break;
		}
		else if (score == scoreSheet[i].score && GameManager::getTime() < scoreSheet[i].time)
		{
			scoreSheet.insert(scoreSheet.begin() + i, temp);
			break;
		}
	}
	if (i == scoreSheet.size() && i < 10)
	{
		scoreSheet.push_back(temp);
	}
	write(scoreSheet);
	totalR = scoreSheet.size();
}

void ScoreManager::nameEntry(int key)
{
	switch (key)
	{
	case GLFW_KEY_ENTER:
		if (!name.empty())
		{
			save();
			menu.nameEntry = 0;
			name.clear();
			menu.setMenu(MenuManager::MAIN);
		}
		break;
	case GLFW_KEY_BACKSPACE:
		if (!name.empty())
		{
			name.pop_back();
		}
	case ' ':
		break;
	default:
		if (name.length() < 17)
		{
			name += key;
		}
		break;
	}
}

GLint ScoreManager::getScore()
{
	return score;
}

void ScoreManager::setScore(GLint s)
{
	score = s;
}
void ScoreManager::save(ofstream& out)
{
	out << score << endl;
}
void ScoreManager::load(ifstream& in)
{
	in >> score;
}