using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AreaSpawner : MonoBehaviour // https://luv-n-interest.tistory.com/684 참고
{
    [SerializeField]
    private GameObject[] areaPrefabs;       //구역으로 사용될 prefab들의 배열
    [SerializeField]
    private int spawnAreaCountAtStart =3;   // 최초 구성될 prefab의 갯수
    [SerializeField]
    private float zDistance = 20;           // 구역 사이의 거리
    private int areaIndex =0;               // 몇번째로 생성된 블록인지 체크하는 용도

    [SerializeField]
    private Transform playerTransform;      //플레이어의 Transform
    
    private void Awake() {
        for(int i=0; i< spawnAreaCountAtStart;i++){
            if(i==0){
                SpawnArea(false);
            }else{
                SpawnArea();
            }
        }
    }

    public void SpawnArea(bool isRandom=true){
        GameObject clone = null;
        if(isRandom==false){
            clone = Instantiate(areaPrefabs[0]);            //areaPrefabs[0]을 생성
        }else{
            int index = Random.Range(0,areaPrefabs.Length);
            clone = Instantiate(areaPrefabs[index]);
        }

        clone.transform.position = new Vector3(0,0,areaIndex * zDistance);
        clone.GetComponent<Area>().Setup(this, playerTransform);
        areaIndex++;
    }

}
