using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collected : MonoBehaviour
{
    // ANIMATION
    private Animator animator;
    scoreCounter script;
    public int totalFruit;

    public AudioSource collected;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        script = GameObject.Find("CountScore").GetComponent<scoreCounter>();

        totalFruit = 0;
        script = GameObject.Find("CountScore").GetComponent<scoreCounter>();
    }

    // Update is called once per frame
    void Update()
    {


    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            script.total_score += 10f;
            animator.SetBool("collected", true);
            script.totalFruit++;
            collected.Play();
        }
    }
}
