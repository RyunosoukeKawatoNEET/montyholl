//Nb2U3LR4

/*
プログラム説明：モンティーホール問題の検証プログラム
作成者:川戸竜之介
作成日:2022/9/6

モンティホール問題は「直感で正しいと思える解答と、論理的に正しい解答が異なる問題」として有名です。
自分自身、解説を聞いてもイマイチ、ピンと来なかったのでこの機会に検証プログラムを作成いたしました。
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void makeRnum(int *num);

int main(void)
{
    double wincount = 0; //当たりを引いた回数
    double count = 0; //試行回数

    char choice1c;//最初に選択するカード番号を受け取る(文字列で受け取る)
    int choise1 = 99; //最初に選択するカード番号を受け取る(数値変換後)
    bool choised1 = false; //最初の選択の正否フラグ
    char choise2; //カードを変更要否を受け取る
    bool choised2 = false; //2番目の選択の正否フラグ
    char choise3; //再度試行するかを受け取る
 
    int hazure=99;//明かされる不正解のカード番号
    bool hazureChoised = false;//明かされる不正解のカード番号の正否フラグ

    int atari;//当たりの番号を格納する
    int atariOutput = 99;//当たりの番号を出力する

    //当たりの番号を乱数生成する
    makeRnum(&atari);

    while (1)
    {
        //プロンプトをリフレッシュする
        system("clear");

        //2回目以降は勝率を出力する
        if (count != 0)
        {
            printf("当たりを引いた確率:%d%%(%d/%d)\n", (int)((wincount / count) * 100), (int)wincount, (int)count);
        }

        printf("1~3のカードが並んでいます。そのうち、1つは当たりです。\n");

        //該当カード上部に×(ハズレ)、◉(当たり)を配置する
        for (int x = 1; x <= 3; x++){
            printf(" ");
            if (x == hazure){
                printf(" × ");
            }else if (x == atariOutput){
                printf(" ◉ ");
            }else{
                printf("   ");
            }
        }

        printf("\n");
        printf(" [1] [2] [3] \n");

        //選択したカード下部に↑を配置する
        switch (choise1)
        {
        case 1:
            printf("  ↑\n");
            break;
        case 2:
            printf("      ↑\n");
            break;
        case 3:
            printf("          ↑\n");
            break;
        default:
            printf("\n");
        }

        printf("\n");

        //プレイヤーへの指示を出力する
        if (choised1)
        {
            if (choised2)
            //正解発表後、3回目の指示を出力する
            {
                //正解か不正解かを判断する
                if (choise1 == atari)
                {
                    printf("当たりを引きました。\n");
                    wincount++;
                }
                else
                {
                    printf("当たりを引けませんでした。\n");
                }
                count++;

                printf("もう一度挑戦する場合は'r'を入力してください※それ以外は終了:");
                rewind(stdin);
                scanf("%c", &choise3);

                //もう一度挑戦する場合、変数を初期化する。
                if (choise3 == 'r')
                {
                    hazure=99;
                    choise1 = 99;
                    choised1 = false;
                    choised2 = false;
                    hazureChoised = false;
                    atariOutput = 99;
                    //当たりを乱数生成する
                    makeRnum(&atari);
                }
                else
                {
                    return 0;
                }
            }
            else
            //2回目の指示を出力する
            {
                printf("%d番目のカードはハズレでした。\n", hazure);
                printf("正解だと思うカードを変更しますか？(y or n):");
                rewind(stdin);
                scanf("%c", &choise2);
                
                if (choise2 == 'y')
                //カードを入れ替える場合
                {
                    choised2 = true;
                    atariOutput = atari;
                    for (int x = 1; x <= 3; x++)
                    //選択していない、カードの番号を捜索する
                    {
                        if (choise1 != x && hazure != x)
                        {
                            choise1 = x;
                            break;
                        }
                    }
                }
                else if (choise2 == 'n')
                {
                    choised2 = true;
                    atariOutput = atari;
                }
            }
        }
        else
        //1回目の指示を出力する
        {
            printf("正解だと思うカードの番号を入力してください。:");
            rewind(stdin);
            scanf("%c", &choice1c);
            if (choice1c == '1' || choice1c == '2' || choice1c == '3')
            {
                choise1 = (int)choice1c - 48;
                choised1 = true;
                while (!hazureChoised)
                {
                    makeRnum(&hazure);
                    if (atari != hazure && choise1 != hazure)
                    {
                        hazureChoised = true;
                    }
                }
            }
        }
    }

    return 0;
}

//乱数を生成する
void makeRnum(int *num)
{
    srand((unsigned int)time(NULL));
    *num = 1 + rand() % 3;
}