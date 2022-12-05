using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class scoreCounter : MonoBehaviour
{
  public float total_score = 0f;
  public int totalFruit;

  [SerializeField] Text countdownText;

  // Start is called before the first frame update
  void Start()
  {
    countdownText.color = Color.black;
    totalFruit = 0;
  }

  void Update()
  {
    countdownText.text = total_score.ToString("0");
  }
}
