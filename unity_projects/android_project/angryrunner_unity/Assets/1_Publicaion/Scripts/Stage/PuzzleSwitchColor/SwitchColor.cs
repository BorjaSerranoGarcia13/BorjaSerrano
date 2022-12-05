using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwitchColor : MonoBehaviour
{
    Material m_Material;
    public bool pressed = false;
    public PuzzleComplete puzzle_object;
    public Color color1;
    public Color color2;

    void Start()
    {
        m_Material = GetComponent<Renderer>().material;
        m_Material.color = color1;
    }

    void Update()
    {
        if (!pressed)
        {
            m_Material.color = color1;
        }
        else
        {
            m_Material.color = color2;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "player")
        {
            if (!puzzle_object.activated)
            {
                if (!pressed)
                { 
                    pressed = true;
                } 
                else if (pressed)
                {
                     pressed = false;
                }
            }
            
        }
    }
}
