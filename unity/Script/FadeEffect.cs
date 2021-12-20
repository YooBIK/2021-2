using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class FadeEffect : MonoBehaviour
{
    [SerializeField]
    private float fadeTime; // 서서히 사라지는 시간을 위한 변수
    private TextMeshProUGUI textFade; // fade효과를 줄 textui

    private void Awake() {
        textFade = GetComponent<TextMeshProUGUI>();

        StartCoroutine(FadeInOut()); // fadeInOut효과 주기 위한 함수 coroutine호출
    }

    private IEnumerator FadeInOut(){ // 0~1 사이로 투명도 반복하여 주는 함수
        while(true){
            yield return StartCoroutine(Fade(1,0));
            yield return StartCoroutine(Fade(0,1));
        }
    }

    private IEnumerator Fade(float start, float end){
        float current =0;
        float percent =0;

        // 한 프레임 시간당 투명도 0~1 사이로 왔다갔다 하여 번쩍번쩍거리는 효과를 위한 함수
        while(percent<1){
            current+=Time.deltaTime;
            percent = current/fadeTime;
            Color color = textFade.color;
            color.a = Mathf.Lerp(start,end,percent);
            textFade.color = color;

            yield return null;
        }
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
