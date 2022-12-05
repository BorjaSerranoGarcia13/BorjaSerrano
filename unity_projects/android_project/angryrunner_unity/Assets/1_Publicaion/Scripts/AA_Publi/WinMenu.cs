using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WinMenu : MonoBehaviour
{
  timeCounter ss;
  scoreCounter aa;
  [SerializeField] Text countdownText1;
  [SerializeField] Text countdownText2;
  [SerializeField] Text countdownText3;

  void Start()
  {
    ss = GameObject.Find("CountTime").GetComponent<timeCounter>();
    aa = GameObject.Find("CountScore").GetComponent<scoreCounter>();
  }

  void Update()
  {
    countdownText3.text = ss.currentTime.ToString("0");
    countdownText2.text = aa.total_score.ToString("0");
    countdownText1.text = aa.totalFruit.ToString("0");
  }
}
