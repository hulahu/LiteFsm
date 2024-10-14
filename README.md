# LiteFSM
`LiteFSM` is a header-only finite state machine for embedded platform base on C++17. This FSM apply simple C++ template programing to keep the code as simple as possible, concept of FSM is driven by Event, protected by Guard and transit by Action, this is easy understand, keep the source code higher readability and convient to maintain or improve.

Benifit from the C++17 features e.g., inline, string_view, structured binding and etc, LiteFSM is better to adapte embedded platform with limite resource, the minumum size of FSM is less than 400 Kbytes. LiteFSM could be easily used in bare-metal system or other embedded RTOS e.g., Free-RTOS.

The only things to apply LiteFSM in your project is import **include** folder to your project, and the **example** will show you how to use LiteFSM.

## Code Examples

 - [Example Project](/example/): A simple stats switching example.

## Changelog

See [CHANGELOG](CHANGELOG.md)

<!-- # Donate
Is LiteFSM help for your?

LiteFSM will continue to develop for free. If support me with a donation will be very appreciated for you!

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com) -->

