[![tutorial-osn-workflow](https://img.shields.io/badge/tutorial--link--of-osn--workflow-blue.svg)](https://github.com/ia-toki/osn-2025/blob/master/WORKFLOW.md)
[![tutorial-git](https://img.shields.io/badge/tutorial--link--of-git-green.svg)](https://about.gitlab.com/images/press/git-cheat-sheet.pdf)

# OSN 2025 Problem Repository

Problem repository of **OSN 2025** (also known internationally as **TOKI Indonesian NOI Open Contest 2025**).

## Problems

| Alias       | Slug                             | Title (id)            | Title (en)            | Type        |
| ----------- | -------------------------------- | --------------------- | --------------------- | ----------- |
| Semifinal A | `osn-2025-semifinal-gulali`      | Gulali 17-an          | N/A                   | Batch       |
| Semifinal B | `osn-2025-semifinal-juragan`     | Juragan Bebek         | N/A                   | Batch       |
| Semifinal C | `osn-2025-semifinal-spiral`      | Kebun Apel            | N/A                   | Batch (\*)  |

(\*) with partial scoring 

| Alias | Slug                  | Title (id)                         | Title (en)               | Type        |
| ----- | --------------------- | ---------------------------------- | ------------------------ | ----------- |
| 0A    | `osn-2025-balik`      | Bebek Pak Dengklek dan Bu Dengklek | N/A                      | Batch       |
| 0B    | `osn-2025-lcmxor`     | Pasangan Malang                    | N/A                      | Batch       |
| 0C    | `osn-2025-batu`       | Es Batu                            | N/A                      | Interactive |
| 1B    | `osn-2025-hujan`      | Taman Hujan                        | Rain Park                | Batch       |
| 1A    | `osn-2025-tarik`      | Larik Tarik                        | Twist List               | Batch       |
| 1C    | `osn-2025-mikroba`    | Mikroba Brantas                    | Brantas Microbes         | Interactive |
| 1A    | `osn-2025-kpk`        | Festival KPK                       | LCM Festival             | Batch       |
| 1B    | `osn-2025-resonansi`  | Pertahanan Malang                  | Malang Defense           | Batch       |
| 1C    | `osn-2025-xor`        | Tukar XOR                          | XOR Exchange             | Batch       |

## Credits

| Alias       | Slug                             | Problem Author(s)                         | Developer(s)                              |
| ----------- | -------------------------------- | ----------------------------------------- | ----------------------------------------- |
| Semifinal A | `osn-2025-semifinal-gulali`      | Mushthofa                                 | Mushthofa                                 |
| Semifinal B | `osn-2025-semifinal-juragan`     | Ashar Fuadi                               | Ashar Fuadi                               |
| Semifinal C | `osn-2025-semifinal-spiral`      | Ammar Fathin Sabili                       | Ammar Fathin Sabili                       |

| Alias | Slug                  | Problem Author(s)                         | Developer(s)                              |
| ----- | --------------------- | ----------------------------------------- | ----------------------------------------- |
| 0A    | `osn-2025-balik`      | Ammar Fathin Sabili                       | Ammar Fathin Sabili                       |
| 0B    | `osn-2025-lcmxor`     | Prabowo Djonatan                          | Prabowo Djonatan                          |
| 0C    | `osn-2025-batu`       | Ammar Fathin Sabili                       | Prabowo Djonatan                          |
| 1A    | `osn-2025-hujan`      | Maximilliano Utomo Quok                   | Maximilliano Utomo Quok                   |
| 1B    | `osn-2025-tarik`      | Prabowo Djonatan                          | Alfonsus Raditya Arsadjaja                |
| 1C    | `osn-2025-mikroba`    | Ammar Fathin Sabili                       | Ammar Fathin Sabili                       |
| 1A    | `osn-2025-kpk`        | Andrew                                    | Andrew                                    |
| 1B    | `osn-2025-resonansi`  | Maximilliano Utomo Quok                   | Maximilliano Utomo Quok                   |
| 1C    | `osn-2025-xor`        | Prabowo Djonatan                          | Prabowo Djonatan                          |

Ashar Fuadi and Joel Gunawan also developed unpublished (backup) problems.

## Upsolving and Editorial

The problem statements and upsolving are available [on TLX](https://tlx.toki.id/problems/osn-2025).

The editorial can also be found on the same link.

## Problem Structure Repository

Each problem contains a problem directory root.

A problem directory root may contain the following files and directories:

* ID problem description (`description-id.html`)
* EN problem description (`description-en.html`)
* Model solution (`solution.cpp`)
* Test case generator (`spec.cpp`)
* Subtasks solution (`solution-<subtask-number>.cpp`)
* Alternative solutions (`solution-<author>-<verdict>-<solution-name>.cpp`)
* Render directory (`render/`)
* Helper directory (`helper/`)
* Communicator (`communicator.cpp`)
* Output validator (`scorer.cpp`)

### ID problem description

Problem description in Bahasa Indonesia. The HTML file uses [Katex](https://katex.org/) syntax to render the math equations. There is a [description header](https://github.com/ia-toki/osn-2025/blob/master/utils/description_header.html) file in `utils/` to render the preview.

### EN problem description

Problem description in the English language.

### Model solution

The solution used to generate the test cases.

### Test case generator

Test case generator using [tcframe](http://tcframe.toki.id/en/stable/) 1.8.0.

### Subtasks solution

Solutions that are used to test the subtasks.

### Alternative solutions

Several alternative and incorrect solutions for testing.

### Render directory

The assets (usually images) that are used by the HTML description file.

### Helper directory

Scripts that may help with problem preparation or the raw files of the assets in `render/`.

### Communicator

For communication in interactive problems, using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#communicator).

### Output validator

To validate solutions that do not use exact match as well as to allow partial scoring, using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#scorer).

## License

All tasks and materials are published under the [Creative Commons Attribution (CC-BY)](https://github.com/ia-toki/osn-2025/blob/master/LICENSE) License.
