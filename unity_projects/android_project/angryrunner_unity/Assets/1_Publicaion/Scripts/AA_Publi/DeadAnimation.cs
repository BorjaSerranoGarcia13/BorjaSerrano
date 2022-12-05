using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DeadAnimation : MonoBehaviour
{
    float transparency;
    PlayerDead script;
    // Start is called before the first frame update
    void Start()
    {
        script = GameObject.Find("Player").GetComponent<PlayerDead>();
        transparency = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (script.player_dead)
        {
          GetComponent<Image>().color = new Color(0,0,0,transparency);
          transparency += 0.5f * Time.deltaTime;
        }
    }
}
