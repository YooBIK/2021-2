using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{   
    bool leftmove = false;
    bool rightmove = false;
    bool jumpflag = false;
    private Movement movement;

    private void Awake(){
        movement = GetComponent<Movement>();        //movement 객체를 넘겨 받음
    }

    // Update is called once per frame
    void Update()
    {
        leftmove=false;
        rightmove=false;
        jumpflag=false;
        if(Input.GetKey(KeyCode.LeftArrow)){        //Left Arrow 키를 입력 받으면 leftmove를 true로 세팅
            leftmove=true;
            movement.MoveToX(-1);                   //movement.MoveToX함수에 -1을 입력값으로 넣어 호출
        }else if(Input.GetKey(KeyCode.RightArrow)){ //Right Arrow 키를 입력 받으면 rightmove를 true로 세팅
            rightmove=true;
            movement.MoveToX(1);                    //movement.MoveToX함수에 1을 입력값으로 넣어 호출
        }else if(Input.GetKey(KeyCode.Space)){      //Space 키를 입력 받으면 jumpflag를 true로 세팅
            jumpflag=true;
            movement.MoveToY();                     //movement.MoveToY함수 호출
        }
    }
}
