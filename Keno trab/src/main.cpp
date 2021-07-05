#include <iostream> // cout
using std::cout;
using std::endl;
#include <string.h> // strtok
#include <stdlib.h> // atof, atoi, rand
#include <vector> // push_back
#include "keno.h"
#include "payoff_table.h"

//Código 1 - recebendo entradas a partir da linha de execução do programa.

using namespace std;

int main(int argc, char *argv[]){

    KenoBet Bet = KenoBet(); // creates empty KenoBet
    unsigned int n_rounds; // number of rounds
    cash_type cp_round;

    cout<<">>>Lendo arquivo de apostas ["<<argv[0]<<"], por favor aguarde"<< endl;
    cout<<"--------------------------------------------------------------------"<< endl;

    if (Bet.set_wage(atof(argv[1])) == false) // reads initial credit (1st arg)
    {
        cout << "Erro na leitura da aposta" << endl;
        return 0;
    }

    cash_type init_wage = Bet.get_wage();

    n_rounds = atoi(argv[2]); // reads number of rounds (2nd arg)

    char * tok; // reads spots (3rd arg)
    tok = strtok(argv[3], " ");
    int spot_unit = atoi(tok);
    while (tok != NULL)
    {
        Bet.add_number(spot_unit);
        tok = strtok(argv[3], " ");
        spot_unit = atoi(tok);
    }

    cp_round = Bet.get_wage()/n_rounds;

    cout << ">>> Aposta lida com sucesso!\n    Você apostará um total de $%" << Bet.get_wage() << " créditos." << endl;
    cout << "    Jogará um total de " << n_rounds << " rodadas, apostando $" << cp_round << " créditos por rodada \n" << endl;
    cout << "    Sua aposta tem " << Bet.size() << " números, eles são: [ ";

    for (auto i : Bet.get_spots())
    {
        cout << i << " ";
    }
    cout << "]" << endl;
    cout << "        ----------+-----------\n        Hits      | Retorno" << endl;

    for (int a = 0;a <= (int)Bet.size();a++)
    {
        cout << "        " << a << "         | " << payoff_t[Bet.size() - 1][a] << endl;
    }
    cout << "        ------------------------------------------------------------" << endl;

    set_of_numbers_type sorted, hits;
    number_type hit;

    for (unsigned int b = 1;b <= n_rounds;b++)
    {
        cout << "        Este é a rodada #" << b << " de " << n_rounds << ", sua aposta é $" << cp_round << ". Boa sorte! \n        Os números sorteados são: [ ";
        for (int c = 0; c < 20;c++)
        {
            hit = rand() % 80 + 1;
            cout << hit << " ";
            sorted.push_back(hit);
        }
        cout << "] \n" << endl;

        hits = Bet.get_hits(sorted);

        cout << "        Você acertou os números [ ";
        int q_hits = 0;
        for (auto hi : hits)
        {
            cout << hi << " ";
            q_hits++;
        }
        cout << "], um total de " << q_hits << " hit(s) de " << Bet.size() << endl;
        cout << "        Sua taxa de retorno é " << payoff_t[Bet.size() - 1][q_hits] << ", assim você sai com: $" << cp_round * payoff_t[Bet.size() - 1][q_hits] << endl;
        Bet.set_wage(Bet.get_wage() + cp_round * payoff_t[Bet.size() - 1][q_hits]);
        cout << "        Você possui um total de: $" << Bet.get_wage() << "créditos." << endl;
        cout << "        ------------------------------------------------------------" << endl;
    }

    cout << ">>> Fim das rodadas! \n--------------------------------------------------------------------\n" << endl;
    cout << "======= Sumário =======\n>>> Você gastou um total de $" << init_wage << " créditos" << endl;
    cout << ">>> Você está saindo do jogo com um total de $" << Bet.get_wage() << " créditos.";
  return 0;
}
