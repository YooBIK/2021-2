using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class BoxCollisionController : MonoBehaviour
{
    [SerializeField]
    private GameObject BoxCollisionEffectPrefab; // box와 충돌 시 이펙트를 가져오기 위한 변수
    // Start is called before the first frame update
    
    // 박스와 충돌 시 
    private void OnTriggerEnter(Collider other) { 
        GameObject clone = Instantiate(BoxCollisionEffectPrefab); // 박스충돌이펙트 생성 
        clone.transform.position = transform.position; // 충돌 시, 박스가 있던 자리에 이펙트 생성
    }
}
