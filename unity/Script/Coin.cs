 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Coin : MonoBehaviour
{
    [SerializeField]
    private GameObject coinEffectPrefab; // 코인 효과를 위한 프리팹 가져오는 변수
    private float rotateSpeed; // 랜덤 회전속도를 위한 변수

    private void Awake() {
        rotateSpeed = Random.Range(0,360); // 랜덤한 회전속도 0~360 뽑기
    }

    void Update()
    {
        transform.Rotate(Vector3.right * rotateSpeed * Time.deltaTime); // 프레임 당 랜덤속도로 회전
    }

    private void OnTriggerEnter(Collider other) { // 코인과 충돌 시 이펙트 처리를 위한 함수
        GameObject clone = Instantiate(coinEffectPrefab); // 이펙트 생성
        clone.transform.position = transform.position; // 코인과 충돌한 자리에 이펙트 생성
        Destroy(gameObject); // 용량 증가를 줄이기 위해 이미 처리된 코인object 삭제
    }
}