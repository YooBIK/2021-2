 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    [SerializeField]
    private GameController gameController;

    private float moveXwidth = 1.5f;    // 이동거리 (x축)
    private float moveTimeX= 0.1f;      // 이동 소요 시간(x축)
    private bool isXmove = false;       // true : 이동 중 false : 이동 가능

    private float originY = 0.55f;      //
    private float gravity = -9.81f;     // 중력
    private float moveTimeY = 0.3f;     // 이동 소요 시간 (y축)
    private bool isJump = false;        // true : 점프중 false : 점프 가능

    [SerializeField]
    private float moveSpeed = 1.0f;     // 전진 속도 (z축)
    private float rotateSpeed = 300.0f; // 회전 속도 (x축 회전), 구르는듯한 모습

    private Rigidbody rigidbody;

    private void Awake(){
        rigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    private void Update() // 매 프레임마다 실행된다.
    {
        if(gameController.IsGameStart==false) return;                       //IsGameStart flag가 true면 밑의 문장 진행
        transform.position += Vector3.forward * moveSpeed *Time.deltaTime;  //일정한 값을 현재 포지션에 계속 더해서 앞으로 진행하는 것처럼 보이게 함

    }


    public void MoveToX(int x){     //입력값으로 +1 or -1을 받음
        if(x>0 && transform.position.x< moveXwidth){        //x>0이고, x< moveXwidth이면, 현재 x좌표를 증가시킨다.
            transform.position = new Vector3(transform.position.x + 0.02f,transform.position.y,transform.position.z);
        }else if(x<0&& transform.position.x > -moveXwidth){ //x<0이고, x> -moveXwidth이면, 현재 x좌표를 감소시킨다.
            transform.position = new Vector3(transform.position.x - 0.02f,transform.position.y,transform.position.z);
        }
    }

    public void MoveToY(){              
        if(isJump ==true)return;        //jump중이면 더이상 점프시키지 않는다.
        StartCoroutine(OnMoveToY());    //juimp중이 아니면 OnMoveToY()를 통해 처리
    }

    private IEnumerator OnMoveToY(){
            float current =0;
            float percent =0;
            float v0 = -gravity;

            isJump = true;                  //점프 시작
            rigidbody.useGravity = false;   //중력 적용 해제
            while(percent < 1 ){                    
                current += Time.deltaTime * 0.5f;   //프레임마다 y좌표를 이동시킨다.
                percent = current/ moveTimeY;       //현재 진행에 대한 퍼센트
                float y = originY + (v0*percent) + (gravity * percent*percent); //퍼센트에 따른 현재 y좌표
                transform.position = new Vector3(transform.position.x,y,transform.position.z);//현재 y좌표를 적용시켜줌
                yield return null;
            }
            isJump=false;                    //점프 끝
            rigidbody.useGravity=true;       //중력 적용 

    }
}
