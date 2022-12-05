using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TakePowerUps : MonoBehaviour
{

    private int power_up_choser = 0;

    cube2 velocidad_cubo;

    public GameObject good_power;
    public GameObject bad_power;

    public GameObject player1;
    public GameObject player2;

    public GameObject goal1;
    public GameObject goal2;
    public AudioSource goal_scaled;

    public GameObject ice1;
    public GameObject speed1;

    public AudioSource slow_audio;

    public AudioSource Take_power;


    void Start()
    {

    }

    IEnumerator goal_scale()
    {

        yield return new WaitForSeconds(0.2f);

        goal_scaled.Play(0);
        goal2.transform.localScale += new Vector3(0.0f, 0.0f, 3.5f);

        yield return new WaitForSeconds(5.0f);

        goal_scaled.Play(0);
        goal2.transform.localScale -= new Vector3(0.0f, 0.0f, 3.5f);


    }

    IEnumerator goal_small()
    {

        yield return new WaitForSeconds(0.2f);

        goal_scaled.Play(0);
        goal1.transform.localScale -= new Vector3(0.0f, 0.0f, 1.5f);

        yield return new WaitForSeconds(5.0f);

        goal_scaled.Play(0);
        goal1.transform.localScale += new Vector3(0.0f, 0.0f, 1.5f);


    }

    IEnumerator slow_effect()
    {

        yield return new WaitForSeconds(0.2f);

        slow_audio.Play(0);
        ice1.SetActive(true);
        cube2 player1speed = player1.GetComponent<cube2>();
        player1speed.speedBall -= 3.0f;
        player1speed.speedNoBall -= 4.0f;

        yield return new WaitForSeconds(5.0f);

        slow_audio.Play(0);
        ice1.SetActive(false);
        player1speed.speedBall += 3.0f;
        player1speed.speedNoBall += 4.0f;

    }

    IEnumerator fast_effect()
    {

        yield return new WaitForSeconds(0.2f);

        slow_audio.Play(0);
        speed1.SetActive(true);
        cube2 player2speed = player2.GetComponent<cube2>();
        player2speed.speedBall += 5.0f;
        player2speed.speedNoBall += 4.0f;

        yield return new WaitForSeconds(5.0f);

        slow_audio.Play(0);
        speed1.SetActive(false);
        player2speed.speedBall -= 5.0f;
        player2speed.speedNoBall -= 4.0f;

    }
    // Update is called once per frame

    void OnTriggerEnter(Collider hit)
    {
        if (hit.gameObject.tag == "power_down")
        {
            Take_power.Play(0);
            bad_power.transform.position = new Vector3(20.87f, 0.55f, 3.28f);
            power_up_choser = Random.Range(0, 2);
            switch (power_up_choser)
            {
                case 0: StartCoroutine(goal_scale());  break;
                case 1: StartCoroutine(slow_effect()); break;
            }
            power_up_choser = 0;
        }

        if (hit.gameObject.tag == "power_up")
        {
            Take_power.Play(0);
            good_power.transform.position = new Vector3(20.87f, 0.55f, 3.28f);
            power_up_choser = Random.Range(0, 2);
            switch (power_up_choser)
            {

                case 0: StartCoroutine(goal_small());  break;
                case 1: StartCoroutine(fast_effect()); break;
            }
            power_up_choser = 0;
        }
    }
}
