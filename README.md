# Katsudon Optimizer

### Setup for Windows Visual Studio

<ol>
<li>
Clone this repo and submodules
<br>
<code>
git clone --recursive https://github.com/DLi7077/Katsudon-Optimizer.git</code>
<br>
then navigate to the folder
<br>
<code>
cd .\Katsudon-Optimizer\
</code>
</li>

<li>
Install vcpkg stuff
<br>
<code>.\vcpkg\bootstrap-vcpkg.bat</code>
</li>

<li>
Install Crow
<br>
<i>This should take around 7 minutes and will take up probably 1GB of space</i>
<br>
<code>
 .\vcpkg\vcpkg install crow:x64-windows
</code>
<br>
vcpkg installs x86 libraries by default. If you are using a x86 system, omit the <code>:x64-windows</code> suffix like so:
<br>
<code>
 .\vcpkg\vcpkg install crow
</code>
<br>
read more here: <a href="https://github.com/microsoft/vcpkg">https://github.com/microsoft/vcpkg</a>
</li>
<li>
Allow Visual Studio to use vcpkg
<br>
<code>.\vcpkg\vcpkg integrate install</code>
</li>
</ol>

<br>

## Character and Enemy Stats

**_All stat calculations should not consider artifact substats_**.

### Bonus stats

| JSON key                   | Description                         | Examples                                    |
| -------------------------- | ----------------------------------- | ------------------------------------------- |
| `"base_attack"`            | Base Attack                         | Character base attack + weapon              |
| `"attack_percent"`         | Bonus Attack%                       | 4pc Noblesse Oblige, Freedom Sworn          |
| `"flat_percent"`           | Bonus Flat Attack                   | Bennet Burst                                |
| `"energy_recharge"`        | Bonus Energy Recharge               | 2pc Emblem of Severed Fate, Ascension Bonus |
| `"elemental_mastery"`      | Bonus Elemental Mastery             | Kazuha C2, Ascension Bonus                  |
| `"crit_damage"`            | Bonus Crit Damage% of the character | 4pc Noblesse Oblige, Freedom Sworn          |
| `"attack_percent"`         | Bonus attack% of the character      | 4pc Noblesse Oblige, Freedom Sworn          |
| `"damage_bonus_elemental"` | Bonus Elemental Damage              | Bennet C6, Ganyu A4 , Ascension Bonus       |
| `"damage_bonus_all"`       | Other Damage Bonus                  | Mona's Omen, Serpent Spine                  |

#### Tartaglia's DPS Ceiling

```js
// Represents Tartaglia's stats without any artifacts
{
  element: "Hydro",              // Tartaglia's Element
  base_attack: 843,              // Base Attack (with Aqua Simulacra)
  crit_damage: 0.882,            // +88.2% Crit Damage (from Aqua Simulacra)
  flat_attack: 1491,             // 1491 bonus Flat Attack from Bennet burst + Adeptus' Temptation
  attack_percent: 1.22,          // +122% Bonus Attack Percent (without artifacts)
  elemental_mastery: 747,        // 747 Bonus Elemental Mastery Key of Khaj-Nisut + Kazuha C2
  damage_bonus_elemental: 1.126, // 112.6% Hydro Damage Bonus (Kazuha + Ascension + Potion)
  damage_bonus_all: 1.0,         // 100% Other Damage Bonus (Mona Omen + Aqua Simulacra)
  ...
};

```

<br>

### Talents

**_Talents will not be identified by Skill/Burst - the user will determine the correct damage bonus for the talent._**

| JSON key           | Description                                |
| ------------------ | ------------------------------------------ |
| `"talent_stat"`    | Final stat value that the talent scales on |
| `"talent_percent"` | Scaling of the talent                      |

### Final Stats

**_Stats that can be used for a talent's scaling stat_**

| JSON key              | Description       |
| --------------------- | ----------------- |
| `"total_attack"`      | Total Attack      |
| `"total_hp"`          | Max HP            |
| `"total_defense"`     | Total Defense     |
| `"elemental_mastery"` | Elemental Mastery |

#### Tartaglia's talents
```js
{
  talent_stat: "total_attack", // Talent scales off total_attack
  talent_percent: 9.86,        // Talent has a 986% scaling
  ...
}
```

<br>

## Enemy Stats

| JSON key                         | Description                                           |
| -------------------------------- | ----------------------------------------------------- |
| `"enemy_level"`                  | The enemy's level                                     |
| `"affected_element"`             | The element that is on the enemy                      |
| `"resistance_to_damage_element"` | The enemy's resistance to the incoming damage element |


#### Enemy's stats
```js
{
  element: "Hydro", // Tartaglia's damaging element from before
  ...,
  enemy_level: 90,                   // Enemy is level 90
  affected_element: "Pyro",          // Enemy is affected by Pyro to enable vaporize
  resistance_to_damage_element: -1.8 // Enemy has -1.8 resistance to Hydro (above)
}
```
