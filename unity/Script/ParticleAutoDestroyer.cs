using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*파티클이 종료된 이후에도 맵에 남아있어 용량을 늘이는것을 방지하기 위한 함수*/
public class ParticleAutoDestroyer : MonoBehaviour
{
private ParticleSystem particle; // 파티클 객체를 가져오기 위한 변수
    private void Awake() {
        particle = GetComponent<ParticleSystem>(); // particle객체 가져오기
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(particle.isPlaying==false){ // 파티클 재생 시간이 끝났을 때,
            Destroy(gameObject); // 파티클 제거
        }
    }
}

