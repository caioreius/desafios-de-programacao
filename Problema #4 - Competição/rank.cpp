#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#define DEBUG(x)

using namespace std;

struct team
{
	int teamId;
	int nProblems;
	int time;
};

struct submission
{
	int teamId;
	int problemId;
	int time;
	char status;
};

int getIndexRankById(vector<team> ranks, int teamId)
{
	int index = 0;
	for (auto rankElement : ranks)
	{
		if (rankElement.teamId == teamId)
			return index;
		index++;
	}

	return -1;
}

void clearProblem(int *arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = 0;
	}
}

team createTeam(int teamId)
{
	team t;
	t.teamId = teamId;
	t.nProblems = 0;
	t.time = 0;

	return t;
}

bool compareTeams(team t1, team t2)
{
	if (t1.nProblems == t2.nProblems)
	{
		if (t1.time == t2.time)
			return t1.teamId > t2.teamId;
		return t1.time > t2.time;
	}
	return t1.nProblems < t2.nProblems;
}

priority_queue<team, vector<team>, function<bool(team, team)>> createRankingQueue()
{
	return priority_queue<team, vector<team>, function<bool(team, team)>>(compareTeams);
}

void ranqueamento(vector<submission> submissions)
{
	vector<team> rank;
	int problems[900];
	int penalty[900];
	clearProblem(problems, 900);
	clearProblem(penalty, 900);
	int teamIndex;
	for (auto s : submissions)
	{

		teamIndex = getIndexRankById(rank, s.teamId);

		if (teamIndex == -1)
		{
			rank.push_back(createTeam(s.teamId));
			teamIndex = rank.size() - 1;
		}

		if (s.status == 'C')
		{
			if (!problems[(s.teamId - 1) * 9 + s.problemId])
			{
				problems[(s.teamId - 1) * 9 + s.problemId] = 1;
				rank.at(teamIndex).time += s.time + penalty[(s.teamId - 1) * 9 + s.problemId];
				rank.at(teamIndex).nProblems += 1;
			}
		}
		else if (s.status == 'I')
		{
			penalty[(s.teamId - 1) * 9 + s.problemId] += 20;
		}
	}

	priority_queue<team, vector<team>, function<bool(team, team)>> rankingQueue = createRankingQueue();
	for (auto t : rank)
	{
		rankingQueue.push(t);
	}

	while (!rankingQueue.empty())
	{
		team t = rankingQueue.top();
		rankingQueue.pop();
		printf("%d %d %d", t.teamId, t.nProblems, t.time);
		printf("\n");
	}

	printf("\n");
}

int main()
{
	vector<submission> submissions;
	submission newSubmission;
	char linha[20];
	int cmp,  // competidor
		prb,  // problema
		tmp;  // tempo
	char msg; // mensagem

	int nComp;
	int fim;
	int i;
	scanf("%d\n", &nComp);
	DEBUG(printf("nComp = %d\n", nComp);)

	while (nComp)
	{
		fim = 0;
		submissions.clear();

		// Leitura de uma competicao
		DEBUG(printf("Leitura de competicao\n");)
		while (!fim && fgets(linha, 20, stdin))
		{
			sscanf(linha, "%d %d %d %c", &cmp, &prb, &tmp, &msg);
			newSubmission.teamId = cmp;
			newSubmission.problemId = prb;
			newSubmission.time = tmp;
			newSubmission.status = msg;

			submissions.push_back(newSubmission);
			DEBUG(printf("C = %d, P = %d, T = %d, M = %c\n", cmp, prb, tmp, msg);)
			if (linha[0] == 10 || linha[0] == 13)
				fim = 1;
		}
		ranqueamento(submissions);

		nComp--;
	}
}
