using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Replay : MonoBehaviour
{
    public void ReplayGame(){

        // 버튼 누를 시, KartRider(처음 씬) 호출
        SceneManager.LoadScene("KartRider");
    }
}
