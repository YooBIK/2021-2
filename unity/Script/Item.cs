using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    [SerializeField]
    private GameObject CFX2_PickupHeartPrefab; // item을 먹고 하트 증가 시 생성되는 이펙트를 위한 변수
    // Start is called before the first frame update
    private void OnTriggerEnter(Collider other) {
        GameObject clone = Instantiate(CFX2_PickupHeartPrefab); // 하트 증가 이펙트 가져오기
        clone.transform.position = transform.position; // item과 충돌 시, item을 먹고 item이 있던 자리에 이펙트 생성
        Destroy(gameObject);
    }
}
