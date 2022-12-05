using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class timeCounter : MonoBehaviour
{
    public float currentTime = 0f;
    public float startingTime = 10f;


    [SerializeField] Text countdownText;

    // Start is called before the first frame update
    void Start()
    {
      currentTime = startingTime;
      countdownText.color = Color.black;
    }

    void Update()
    {
      if (currentTime > 0) currentTime -= 1 * Time.deltaTime;
      else currentTime = 0;

      countdownText.text = currentTime.ToString("0");

    }

}
