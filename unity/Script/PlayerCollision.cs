using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class PlayerCollision : MonoBehaviour
{
    [SerializeField]
    private GameController gameController; // gamecontroller 호출을 위한 변수
    
    
    /*충돌 처리 함수*/
    private void OnTriggerEnter(Collider other) {
        if(other.tag.Equals("Obstacle")){ // tag가 obstacle인 물체(박스, 허들, 등) 와 Player 충돌 시
            gameController.decreaseLife(); // 생명 1 감소
        }else if(other.tag.Equals("Coin")){ // 작은 coin과 충돌 시
            gameController.IncreaseCoinCount(); // coincount변수 1 추가
        }else if(other.tag.Equals("BigCoin")){ // 대왕 coin과 충돌 시
            gameController.IncreaseBigCoinCount(); // Bigcoincount 함수(coincount 5개 증가) 호출
        }else if(other.tag.Equals("Item")){         // Item과 충돌시
            gameController.IncreaseLife();          // IncreaseLife 함수(life 1 증가) 호출
        }
    }
    // Start is called before the first frame update
    void Start()
    {
    }
    // Update is called once per frame
    void Update()
    {
    }
}
