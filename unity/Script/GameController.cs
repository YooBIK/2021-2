using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro; 
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour
{
    [SerializeField]
    private TextMeshProUGUI textTitleFirst;
    [SerializeField]
    private TextMeshProUGUI textTitleSec;
    [SerializeField]
    private TextMeshProUGUI textTapToPlay;
    [SerializeField]
    private TextMeshProUGUI textCoinCount;
    [SerializeField]
    private TextMeshProUGUI Life;
    public static int coincount;   // coin를 카운트하기 위한 변수(점수와 관련)
    public static int bestcc=0;      // best score저장을 위한 변수
    int life;


 
    public bool IsGameStart{private set;get;}
    
    private void Awake() {              //텍스트들의 활성화 유무와 게임의 시작 유무를 플레그로 체크
        IsGameStart = false;
        textTitleFirst.enabled = true;
        textTitleSec.enabled = true;
        textTapToPlay.enabled = true;
        textCoinCount.enabled = false;  
        Life.enabled = false;
    }

    // Start is called before the first frame update
    private IEnumerator Start()
    {
        life=5;                         // 시작 시 life 초기화
        coincount=0;                    // 시작 시 coin개수 초기화

        while(true){                                //게임시작 신호(마우스 클릭)이 오기 전까지 루프를 돌며 대기한다.
            if(Input.GetMouseButtonDown(0)){        //시작 신호가 오면 활성화 되어야 하는 텍스트들을 활성화 시켜주고
                IsGameStart = true;                 //IsGameStart 플레그를 true로 설정하며 무한 루프를 나온다.
                textTitleFirst.enabled = false;
                textTitleSec.enabled = false;
                textTapToPlay.enabled = false;
                textCoinCount.enabled = true;
                Life.enabled = true;
                break;
            }
            yield return null;
        }
    }

    public void IncreaseCoinCount(){
        coincount++;                        //코인의 개수를 늘린다.
        if(coincount%50==0&&life<5){        //coincount가 50의 배수일 때, life가 5미만이면 life를 증가시킨다.
            life++;
            showLife();
        }
        textCoinCount.text = coincount.ToString();  //scene에서 coincount부분의 숫자를 업데이트 시킨다.
    }

    public void IncreaseBigCoinCount(){         //BigCoin에 대한 처리
        int before_count = coincount;           // 이전 코인의 개수를 저장
        coincount += 5;                         // 코인의 개수를 5개 증가시킨다.
        if(life<5&&before_count%50 > coincount%50){ // life가 5 미만이고, BigCoin을 먹으면서 50을 넘었으면, life를 증가시킨다.
            life++;
            showLife();
        }
        textCoinCount.text = coincount.ToString(); //scene에서 coincount부분의 숫자를 업데이트 시킨다.
    }

    public void IncreaseLife(){
        life = life + 1;
        showLife();
    }

    public void decreaseLife(){
        life--;
        showLife();
    }

    public void showLife(){             //현재 life의 수를 ♥의 개수로 보여준다.
        string str = "";
        for(int i=0;i<life;i++){
            str += "♥";
        }
        Life.text = str;

        if(coincount>bestcc){           //최고 점수를 저장한다.
            bestcc=coincount;
        }

        if(life==0){
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            SceneManager.LoadScene("GameOver");     //life를 모두 소모하면 GameOver씬으로 넘어간다.
        }
    }

}
