using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Area : MonoBehaviour{ // https://luv-n-interest.tistory.com/684 참고
    [SerializeField]
    private float destroyDistance= 15;
    private AreaSpawner areaSpawner;
    private Transform playerTransform;

    public void Setup(AreaSpawner areaSpawner, Transform playerTransform){
        this.areaSpawner = areaSpawner;
        this.playerTransform = playerTransform;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(playerTransform.position.z - transform.position.z >= destroyDistance){
            areaSpawner.SpawnArea();
            Destroy(gameObject);
        }
    }
}
