using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{   
    [SerializeField]
    private Transform target;       //카메라가 추적하는 객체(player)
    private float zDistance;        //카메라와 객체 사이의 z 거리

    // Start is called before the first frame update
    private void Awake() {
        if(target!= null){
            zDistance = target.position.z - transform.position.z;   //초기 카메라의 z좌표와 
                                                                    //타겟의 z좌표 사이의 거리를 zDistance로 설정
        }
    }

    private void LateUpdate() {
        if(target == null)return;
        Vector3 position = transform.position;
        position.z = target.position.z - zDistance;     //현재 z좌표를 target의 z좌표 - zDistance로 설정
        transform.position = position;                  //이동 변환 적용
    }
}
