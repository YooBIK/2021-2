using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class bestscore : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        // text component 가져와서 현재의 best score gameover화면에 출력
        GetComponent<Text>().text = "Best^_^ : "+GameController.bestcc.ToString();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
