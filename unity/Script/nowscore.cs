using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class nowscore : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //currentscore 반영
        GetComponent<Text>().text = "Score : "+GameController.coincount.ToString();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
